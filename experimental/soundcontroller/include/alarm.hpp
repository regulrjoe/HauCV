#ifndef ALARM_HPP
#define ALARM_HPP

#include "alarm_commands.hpp"
#include "zmq_config.hpp"
#include <zmq.hpp>
#include <string>

namespace hcv
{
	class Alarm
	{
		public:
			//Alarm(const std::string&);
			Alarm();
			~Alarm();
			static void Spawn(zmq::context_t*, const std::string&);
			static std::string GetAddress();

		private:
			friend AlarmCommand;
			static void doProcess(zmq::pollitem_t*);
			static void handleRequest(zmq::pollitem_t*);
			static void play();
			static void start();
			static void stop();
			static void shutdown();

		private:
			static ZMQConfig zmq_config;
			static std::string sound;
			static bool is_shutting_down;
			static bool is_playing;
	};

} // namespace hcv

#endif // ALARM_HPP
