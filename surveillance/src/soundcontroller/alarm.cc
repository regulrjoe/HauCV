#include "soundcontroller/alarm.hpp"
#include "soundcontroller/zmq_message.hpp"
#include <dbg.h>

#include <iostream>
#include <chrono>
#include <thread>

#include <stdlib.h>

using namespace std;

namespace hcv
{

	Alarm::Alarm()
	{
		dbg("Alarm Constructed.");

		m_zmq_config = {
			nullptr, // zmq::context_t*
			nullptr, // zmq::socket_t*
			"inproc://alarm" // address
		};

		m_playing_flag = false;
		m_shutdown_flag = false;
	}

	Alarm::~Alarm()
	{
		dbg("Alarm Destroyed.");
	}

	string Alarm::GetAddress()
	{
		return m_zmq_config.address;
	}

	///////////////////////
	void Alarm::Init(zmq::context_t* i_context, const string& i_soundfile)
	{
		try
		{
			m_zmq_config = {
				i_context,
				new zmq::socket_t(*i_context, ZMQ_PAIR),
				"inproc://alarm"
			};

			m_zmq_config.socket->bind(m_zmq_config.address);

			m_pollitem[0] = {
				static_cast<void*>(*(m_zmq_config.socket)),
				0,
				ZMQ_POLLIN,
				0
			};

			dbg(m_soundfile = i_soundfile);
		}
		catch (...)
		{
			dbg("Exception.");
		}

	}

	///////////////////////
	void Alarm::Run(Alarm* i_alarm_ptr)
	{
		zmq::message_t request;
		ZMQMessage* reply_ptr = new ZMQMessage();
		AlarmCommand* command_ptr = NULL;

		int ret;
		while (true)
		{
			zmq::poll(i_alarm_ptr->m_pollitem, 1, 0);

			if (ret < 0) // exception
			{
				reply_ptr->data = -1;
				i_alarm_ptr->m_zmq_config.socket->send(reply_ptr, sizeof(ZMQMessage));
			}

			// If there is an event to handle.
			if (i_alarm_ptr->m_pollitem->revents & ZMQ_POLLIN)
			{
				i_alarm_ptr->m_zmq_config.socket->recv(&request);
				command_ptr = (AlarmCommand*)request.data();

				command_ptr->Execute();
				reply_ptr->data = 0;
				i_alarm_ptr->m_zmq_config.socket->send(reply_ptr, sizeof(ZMQMessage));
			}

			if (i_alarm_ptr->m_shutdown_flag)
				break;

			if (i_alarm_ptr->m_playing_flag)
				i_alarm_ptr->play();
			else
				this_thread::sleep_for(chrono::milliseconds(1000));
		}

		i_alarm_ptr->m_zmq_config.socket->close();
	}

	///////////////////////
	void Alarm::start()
	{
		m_playing_flag = true;
		dbg(m_playing_flag);
	}

	///////////////////////
	void Alarm::stop()
	{
		m_playing_flag = false;
		dbg(m_playing_flag);
	}

	///////////////////////
	void Alarm::play()
	{
		this_thread::sleep_for(chrono::milliseconds(1000));
		dbg("Playing alarm.");
		string player = "mpg123 " + m_soundfile;
		system(player.c_str());
	}

	///////////////////////
	void Alarm::shutdown()
	{
		m_shutdown_flag = true;
		dbg(m_shutdown_flag);
	}

} // namespace hcv

