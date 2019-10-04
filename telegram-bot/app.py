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
