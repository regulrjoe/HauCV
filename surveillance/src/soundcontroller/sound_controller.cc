#include "soundcontroller/sound_controller.hpp"

#include <iostream>
#include <thread>

using namespace std;

namespace hcv
{
	/////////////////////////
	SoundController::SoundController(const string& i_alarm_soundfile, const string& i_alert_soundfile) : m_alarm_thread{}, m_alarm_soundfile(i_alarm_soundfile), m_alert_soundfile(i_alert_soundfile)
	{
		cout << "SoundController Constructor." << endl;

		m_init_flag = false;
	}

	/////////////////////////
	SoundController::~SoundController()
	{
		cout << "SoundController Destructor." << endl;

		if (m_init_flag)
		{
			m_alarm_thread.join();
			m_alarm_zmq_config.socket->close();
			m_alarm_zmq_config.context->close();
		}
	}

	////////////////////////
	void SoundController::Init(zmq::context_t* i_context)
	{
		m_alarm_ptr = new Alarm();
		m_alarm_zmq_config.context = i_context;
		m_alarm_zmq_config.socket = new zmq::socket_t(*i_context, ZMQ_PAIR);
		m_alarm_zmq_config.address = m_alarm_ptr->GetAddress();
		m_alarm_zmq_config.socket->connect(m_alarm_zmq_config.address);

		m_alarm_ptr->Init(i_context, m_alarm_soundfile);
		
		m_alarm_thread = thread{Alarm::Run, m_alarm_ptr};
		m_init_flag = true;
	}

	/////////////////////////
	void SoundController::StartAlarm()
	{
		zmq::message_t reply;
		AlarmCommand* command = new StartAlarmCommand(m_alarm_ptr);
		m_alarm_zmq_config.socket->send(command, sizeof(StartAlarmCommand));
		m_alarm_zmq_config.socket->recv(&reply);
	}

	/////////////////////////
	void SoundController::StopAlarm()
	{
		zmq::message_t reply;
		AlarmCommand* command = new StopAlarmCommand(m_alarm_ptr);
		m_alarm_zmq_config.socket->send(command, sizeof(StopAlarmCommand));
		m_alarm_zmq_config.socket->recv(&reply);
	}

	/////////////////////////
	void SoundController::ShutdownAlarm()
	{
		zmq::message_t reply;
		AlarmCommand* command = new ShutdownAlarmCommand(m_alarm_ptr);
		m_alarm_zmq_config.socket->send(command, sizeof(ShutdownAlarmCommand));
		m_alarm_zmq_config.socket->recv(&reply);

		if (m_init_flag)
		{
			m_alarm_thread.join();
			m_alarm_zmq_config.socket->close();
			m_alarm_zmq_config.context->close();
			m_init_flag = false;
		}
	}

} // namespace hcv

