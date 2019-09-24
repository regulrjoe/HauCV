#ifndef SOUND_CONTROLLER_HPP
#define SOUND_CONTROLLER_HPP

#include "soundcontroller/alarm.hpp"
#include "soundcontroller/zmq_config.hpp"
#include <zmq.hpp>
#include <string>
#include <thread>

namespace hcv
{
	class SoundController
	{
		public:
			SoundController(const std::string&, const std::string&);
			~SoundController();

			void Init(zmq::context_t*);
			void StartAlarm();
			void StopAlarm();
			void ShutdownAlarm();

		private:
			ZMQConfig m_alarm_zmq_config;
			Alarm* m_alarm_ptr;
			std::thread m_alarm_thread;
			bool m_init_flag;
			std::string m_alarm_soundfile;
			std::string m_alert_soundfile;
	};

} // namespace hcv

#endif // SOUND_CONTROLLER_HPP
