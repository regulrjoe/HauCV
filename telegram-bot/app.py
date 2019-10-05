import sys
import os
import logging

import pymongo
from pymongo import MongoClient
from pymongo.errors import ConnectionFailure

logging.basicConfig(format='%(asctime)s - %(name)s - %(levelname)s - %(message)s', level=logging.INFO)

mongoclient = MongoClient(os.environ['MONGO_URL'])

# Check if connection to mongodb is authorized
try:
    mongoclient.admin.command('ismaster')
except ConnectionFailure:
    logging.exception('Connection to mongodb not authorized. Check your credentials in docker-compose.yml')
    sys.exit(1)

logging.info('Connection with mongodb established.')
hausdb = mongoclient.hauscv

from telegram.ext import Updater
from telegram.ext import CommandHandler
from telegram.ext import MessageHandler, Filters

updater = Updater(token=os.environ['TELEGRAM_TOKEN'], use_context=True)

dispatcher = updater.dispatcher

def start(update, context):
    chat_id = update.message.chat_id
    username = update.message.from_user.username
    first_name = update.message.from_user.first_name
    logging.info(f'New /start message received from {chat_id}')
    try:
        user = hausdb.users.find_one({'telegram_chat_id': chat_id})
    except pymongo.errors.PyMongoError:
        logging.exception('Query to Users collection failed.')
        sys.exit(1)

    if user is None:

        try:
            new_user = {'telegram_chat_id': chat_id, 'username': username, 'first_name': first_name}
            new_user_id = hausdb.users.insert_one(new_user)
            logging.info(f'New user {new_user_id} persisted to DB with chat_id {chat_id}')
        except pymongo.errors.PyMongoError:
            logging.exception('Insertion of new user failed.')
            sys.exit(1)

        context.bot.send_message(chat_id=chat_id, text=f"Hi {first_name} welcome to your HausCV!")

    else:
        logging.info(f'User with chat_id {chat_id} already exists in DB.')
        context.bot.send_message(chat_id=chat_id, text=f"Oh! Looks like you're already registered to your HausCV!")

start_handler = CommandHandler('start', start)
dispatcher.add_handler(start_handler)


def unknown(update, context):
    context.bot.send_message(chat_id=update.message.chat_id, text="Sorry, I don't understand that command.")

unknown_handler = MessageHandler(Filters.command, unknown)
dispatcher.add_handler(unknown_handler)


logging.info('Polling now for new messages.')

updater.start_polling()
