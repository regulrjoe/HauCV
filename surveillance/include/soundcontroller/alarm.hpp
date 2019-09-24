#ifndef ALARM_HPP
#define ALARM_HPP

#include "soundcontroller/alarm_commands.hpp"
#include "soundcontroller/zmq_config.hpp"
#include <zmq.hpp>
#include <string>

namespace hcv
{
	class Alarm
	{
		public:
			Alarm();
			~Alarm();

			static void Run(Alarm*);
			void Init(zmq::context_t*, const std::string&);
			std::string GetAddress();
			
		private:
			friend  StartAlarmCommand;
			friend  StopAlarmCommand;
			friend  ShutdownAlarmCommand;
			void start();
			void stop();
			void shutdown();
			void play();

		private:
			bool m_playing_flag;
			bool m_shutdown_flag;
			std::string m_soundfile;
			ZMQConfig m_zmq_config;
			zmq::pollitem_t m_pollitem[1];
	};

} // namespace hcv

#endif // ALARM_HPP
