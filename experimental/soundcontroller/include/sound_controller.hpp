#ifndef SOUND_CONTROLLER_HPP
#define SOUND_CONTROLLER_HPP

#include <zmq.hpp>

#include <string>

namespace hcv
{
	class SoundController
	{
		public:
			SoundController();
			~SoundController();

			static void Init(zmq::context_t*);
			static std::string GetAddr();


		private:
			static void doProcess();
			static void doPlayAlert();
			static void doPlayAlarm();
			static void doStartAlarm();
			static void doStopAlarm();

		private:
			static bool m_alarm_playing;

			static std::string m_alarm_sound;
			static std::string m_alert_sound;
			static std::string m_addr;

			static zmq::context_t* m_context;
			static zmq::socket_t* m_socket;
			static zmq::pollitem_t m_items[1];
	};

	struct IntMessage
	{
		int data;
	};
} // namespace hcv

#endif // SOUND_CONTROLLER_HPP
