#ifndef ALARM_HPP
#define ALARM_HPP

#include "alarm/alarm_commands.hpp"
#include "alarm/alarm_states.hpp"
#include "conn/zmq_config.hpp"

#include <zmq.hpp>

#include <string>

namespace hcv
{
	class Alarm
	{
		friend class IAlarmState;

		public:
			Alarm(const std::string&);
			~Alarm();

			static void Run(Alarm*);

			void Init(zmq::context_t* const);
			void Start();
			void Stop();
			void Shutdown();
			void SetSoundfile(const std::string&);
			const std::string GetAddress();
			const std::string GetSoundfile();

		private:
			void changeState(IAlarmState*);
			void handleRequest(Alarm*);
			void play();

			bool m_shutdown_flag;
			std::string m_soundfile;
			IAlarmState* m_state_ptr;
			
			ZMQConfig m_zmq_config;
			zmq::pollitem_t m_pollitem[1];
	};
} // namespace hcv

#endif // ALARM_HPP
