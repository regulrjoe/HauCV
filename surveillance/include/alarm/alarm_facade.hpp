#ifndef ALARM_FACADE_HPP
#define ALARM_FACADE_HPP

#include "alarm/alarm.hpp"
#include "conn/zmq_config.hpp"

#include <zmq.hpp>
#include <string>
#include <thread>

namespace hcv
{
	class AlarmFacade
	{
		public:
			AlarmFacade(Alarm*);
			~AlarmFacade();

			void Init(zmq::context_t* const);
			void Start();
			void Stop();
			void Shutdown();
			void UpdateSoundfile(const std::string&);

		private:
			Alarm* m_alarm_ptr;
			ZMQConfig m_alarm_zmq_config;
			std::thread m_alarm_thread;
			bool m_alarm_thread_is_running;
	};
} // namespace hcv

#endif // ALARM_FACADE_HPP
