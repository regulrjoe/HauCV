#include "alarm/alarm.hpp"
#include "conn/zmq_message.hpp"

#include "utils/macros.hpp"
#include "utils/rcode.hpp"

#include <iostream>
#include <chrono>
#include <thread>

#include <stdlib.h>

using namespace std;

namespace hcv
{

	///////////////////////
	Alarm::Alarm(const string& i_soundfile) : m_soundfile(i_soundfile)
	{
		dbg("Alarm::Alarm()");
//		printINFO("Alarm Constructed");

		m_zmq_config = {
			nullptr, // zmq::context_t*
			nullptr, // zmq::socket_t*
			"inproc://alarm" // address
		};

		m_shutdown_flag = false;

		m_state_ptr = InactiveAlarmState::Instance();
	}

	///////////////////////
	Alarm::~Alarm()
	{
		dbg("Alarm::~Alarm()");
//		printINFO("Alarm Destroyed");
	}

	///////////////////////
	const string Alarm::GetAddress()
	{
		dbg("Alarm::GetAddress()");
		return m_zmq_config.address;
	}

	///////////////////////
	const string Alarm::GetSoundfile()
	{
		dbg("Alarm::GetSoundfile()");
		return m_soundfile;
	}

	///////////////////////
	void Alarm::Init(zmq::context_t* const i_context)
	{
		dbg("Alarm::Init()");
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
		}
		catch (const zmq::error_t& e)
		{
			printERROR(e.what());
		}
	}

	///////////////////////
	void Alarm::Run(Alarm* i_alarm_ptr)
	{
		dbg("Alarm::Run()");
		while (true)
		{
			i_alarm_ptr->handleRequest(i_alarm_ptr);

			if (i_alarm_ptr->m_shutdown_flag)
				break;

			i_alarm_ptr->play();
		}

		i_alarm_ptr->m_zmq_config.socket->close();
	}
	///////////////////////
	void Alarm::handleRequest(Alarm* i_alarm_ptr)
	{
		int ret = zmq::poll(i_alarm_ptr->m_pollitem, 1, 0);

		if (ret < 0) // exception
		{
			ZMQMessage* reply_ptr = new ZMQMessage();

			reply_ptr->data = -1;

			i_alarm_ptr->m_zmq_config.socket->send(reply_ptr, sizeof(ZMQMessage));
		}

		// If there is an event to handle.
		if (i_alarm_ptr->m_pollitem->revents & ZMQ_POLLIN)
		{
			zmq::message_t request;
			ZMQMessage* reply_ptr = new ZMQMessage();
			AlarmCommand* command_ptr = NULL;

			i_alarm_ptr->m_zmq_config.socket->recv(&request);
			command_ptr = (AlarmCommand*)request.data();

			try
			{
				command_ptr->Execute();

				reply_ptr->data = 0;
			}
			catch (const RCode& rc)
			{
				printERROR(RCMsg(rc)); // TODO: change form printERROR to printRC and let RC decide severity of message.

				reply_ptr->data = static_cast<int>(rc);
			}
			catch (const exception& e)
			{
				printERROR(e.what());

				reply_ptr->data = -1;
			}

			i_alarm_ptr->m_zmq_config.socket->send(reply_ptr, sizeof(ZMQMessage));
		}
	}

	///////////////////////
	void Alarm::Start()
	{
		dbg("Alarm::Start()");
		m_state_ptr->Start(this);
	}

	///////////////////////
	void Alarm::Stop()
	{
		dbg("Alarm::Stop()");
		m_state_ptr->Stop(this);
	}

	///////////////////////
	void Alarm::Shutdown()
	{
		dbg("Alarm::Shutdown()");
		m_shutdown_flag = true;
	}

	///////////////////////
	void Alarm::play()
	{
		try
		{		
			m_state_ptr->Play(this);
		}
		catch (const exception& e)
		{
			printERROR(e.what());
		}
	}
	
	///////////////////////
	void Alarm::SetSoundfile(const string& i_soundfile)
	{
		dbg("Alarm::SetSoundfile()");
		m_soundfile = i_soundfile;
	}

	///////////////////////
	void Alarm::changeState(IAlarmState* i_state_ptr)
	{
		dbg("Alarm::changeState()");
		m_state_ptr = i_state_ptr;
	}

} // namespace hcv

