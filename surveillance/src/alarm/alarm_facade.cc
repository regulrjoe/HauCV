#include "alarm/alarm_facade.hpp"

#include "utils/rcode.hpp"
#include "utils/macros.hpp"

#include <dbg.h>

using namespace std;

namespace hcv
{
	/////////////////////////
	AlarmFacade::AlarmFacade(Alarm* i_alarm_ptr) : m_alarm_ptr(i_alarm_ptr)
	{
		dbg("AlarmFacade::AlarmFacade()");
		//printINFO("Constructor.");

		m_alarm_thread_is_running = false;
	}

	/////////////////////////
	AlarmFacade::~AlarmFacade()
	{
		dbg("AlarmFacade::~AlarmFacade()");
		//printINFO("Destructor.");

		if (m_alarm_thread_is_running)
			this->Shutdown();
	}

	/////////////////////////
	void AlarmFacade::Init(zmq::context_t* const i_context)
	{
		dbg("AlarmFacade::Init()");
		try
		{
			if (m_alarm_thread_is_running)
				throw RCode::NOTOK; // TODO: Specify better error.
				// Alarm has already been initialized. You must shut it down (with AlarmFacade::Shutdown()) before Initializing it again.

			m_alarm_zmq_config.context = i_context;
			m_alarm_zmq_config.socket = new zmq::socket_t(*i_context, ZMQ_PAIR);
			m_alarm_zmq_config.address = m_alarm_ptr->GetAddress();
			m_alarm_zmq_config.socket->connect(m_alarm_zmq_config.address);

			m_alarm_ptr->Init(i_context);

			m_alarm_thread = thread{Alarm::Run, m_alarm_ptr};

			m_alarm_thread_is_running = true;
		}
		catch (const RCode& rc)
		{
			printERROR(RCMsg(rc));
			throw rc;
		}
		catch (const exception& e)
		{
			printERROR(e.what());
			throw e;
		}
	}

	/////////////////////////
	void AlarmFacade::Start()
	{
		dbg("AlarmFacade::Start()");
		try
		{
			if (!m_alarm_thread_is_running)
				throw RCode::NOTOK; // TODO: Specify better error.
				//You must Initialize the AlarmFacade before handling the Alarm.

			zmq::message_t reply;
			AlarmCommand* command = new StartAlarmCommand(m_alarm_ptr);

			m_alarm_zmq_config.socket->send(command, sizeof(StartAlarmCommand));
			
			m_alarm_zmq_config.socket->recv(&reply);

			// TODO: Handle reply.
		}
		catch (const RCode& rc)
		{
			printERROR(RCMsg(rc));
			throw rc;
		}
		catch (const exception& e)
		{
			printERROR(e.what());
			throw e;
		}
	}


	/////////////////////////
	void AlarmFacade::Stop()
	{
		dbg("AlarmFacade::Stop()");
		try
		{
			if (!m_alarm_thread_is_running)
				throw RCode::NOTOK; // TODO. Specify better error.

			zmq::message_t reply;
			AlarmCommand* command = new StopAlarmCommand(m_alarm_ptr);

			m_alarm_zmq_config.socket->send(command, sizeof(StopAlarmCommand));
			
			m_alarm_zmq_config.socket->recv(&reply);

			// TODO: Handle reply.
		}
		catch (const RCode& rc)
		{
			printERROR(RCMsg(rc));
			throw rc;
		}
		catch (const exception& e)
		{
			printERROR(e.what());
			throw e;
		}
	}

	/////////////////////////
	void AlarmFacade::Shutdown()
	{
		dbg("AlarmFacade::Shutdown()");
		try
		{
			if (!m_alarm_thread_is_running)
				throw RCode::NOTOK; // TODO: Specify better error.

			zmq::message_t reply;
			AlarmCommand* command = new ShutdownAlarmCommand(m_alarm_ptr);

			m_alarm_zmq_config.socket->send(command, sizeof(ShutdownAlarmCommand));
			m_alarm_zmq_config.socket->recv(&reply);

			// TODO: Handle reply.
		}
		catch (const RCode& rc)
		{
			printERROR(RCMsg(rc));
			throw rc;
		}
		catch (const exception& e)
		{
			printERROR(e.what());
			throw e;
		}
	}

	/////////////////////////
	void AlarmFacade::UpdateSoundfile(const string& i_soundfile)
	{
		dbg("AlarmFacade::UpdateSoundfile()");
		try
		{
			if (!m_alarm_thread_is_running)
				throw RCode::NOTOK; // TODO. Specify better error.

			zmq::message_t reply;
			AlarmCommand* command = new UpdateSoundfileAlarmCommand(m_alarm_ptr, i_soundfile);

			m_alarm_zmq_config.socket->send(command, sizeof(UpdateSoundfileAlarmCommand));
			m_alarm_zmq_config.socket->recv(&reply);

			// TODO: Handle reply.
		}
		catch (const RCode& rc)
		{
			printERROR(RCMsg(rc));
			throw rc;
		}
		catch (const exception& e)
		{
			printERROR(e.what());
			throw e;
		}
	}
} // namespace hcv
