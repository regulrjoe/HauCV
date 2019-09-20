#include "alarm.hpp"
#include "zmq_message.hpp"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

namespace hcv
{
	string Alarm::sound = "";
	bool Alarm::is_playing = false;
	bool Alarm::is_shutting_down = false;

	ZMQConfig Alarm::zmq_config = {
		nullptr, // zmq::context_t*
		nullptr, // zmq::socket_t*
		"inproc://alarm" // address
	};

	Alarm::Alarm(/*const string& i_sound*/)
	{
		cout << "Alarm::Alarm()" << endl;

		//Alarm::sound = i_sound;
	}

	Alarm::~Alarm()
	{
		cout << "Alarm::~Alarm()" << endl;
	}

	string Alarm::GetAddress()
	{
		cout << "Alarm::GetAddress()" << endl;
		return Alarm::zmq_config.address;
	}

	///////////////////////
	void Alarm::Spawn(zmq::context_t* i_context, const string& i_sound)
	{
		cout << "Alarm::Spawn()" << endl;

		Alarm::zmq_config.context = i_context;
		Alarm::zmq_config.socket = new zmq::socket_t(*i_context, ZMQ_PAIR);
		Alarm::zmq_config.socket->bind(Alarm::zmq_config.address);

		zmq::pollitem_t items[] = {
			{ static_cast<void*>(*(Alarm::zmq_config.socket)), 0, ZMQ_POLLIN, 0 }
		};

		Alarm::sound = i_sound;

		Alarm::doProcess(items);

		Alarm::zmq_config.socket->close();
	}

	///////////////////////
	void Alarm::doProcess(zmq::pollitem_t* i_pollitem)
	{
		cout << "Alarm::doProcess()" << endl;

		while (true)
		{
			Alarm::handleRequest(i_pollitem);

			if (Alarm::is_shutting_down)
				break;

			if (Alarm::is_playing)
				Alarm::play();
			else
				this_thread::sleep_for(chrono::milliseconds(1000));
		}

		cout << "Exiting Alarm::doProcess()" << endl;
	}

	///////////////////////
	void Alarm::handleRequest(zmq::pollitem_t* i_pollitem)
	{
		zmq::message_t request;
		ZMQMessage* message = new ZMQMessage();

		int ret = zmq::poll(i_pollitem, 1, 0);

		if (ret < 0) // exception
		{
			message->data = -1;
			Alarm::zmq_config.socket->send(message, sizeof(ZMQMessage));
		}

		// If there is an event to handle.
		if (i_pollitem->revents & ZMQ_POLLIN)
		{
			Alarm::zmq_config.socket->recv(&request);
			message = (ZMQMessage*)request.data();
			cout << "Incoming message: " << message->data << endl;

			if (message->data == 0) // Shutdown
			{
				Alarm::shutdown();
				Alarm::zmq_config.socket->send(message, sizeof(ZMQMessage));
			}
			else if (message->data == 1) // Start Alarm
			{
				Alarm::start();
				Alarm::zmq_config.socket->send(message, sizeof(ZMQMessage));
			}
			else if (message->data == 2) // Stop Alarm
			{
				Alarm::stop();
				Alarm::zmq_config.socket->send(message, sizeof(ZMQMessage));
			}
			else // Unrecognized command
			{
				message->data = -1;
				Alarm::zmq_config.socket->send(message, sizeof(ZMQMessage));
			}
		}
	}

	///////////////////////
	void Alarm::start()
	{
		cout << "Alarm::start()" << endl;
		Alarm::is_playing = true;
	}

	///////////////////////
	void Alarm::stop()
	{
		cout << "Alarm::stop()" << endl;
		Alarm::is_playing = false;
	}

	///////////////////////
	void Alarm::play()
	{
		cout << "Alarm::play()" << endl;
		// TODO
	}

	///////////////////////
	void Alarm::shutdown()
	{
		cout << "Alarm::shutdown()" << endl;
		Alarm::is_shutting_down = true;
	}

} // namespace hcv

