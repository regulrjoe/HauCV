#ifndef FD_TIMER_HPP
#define FD_TIMER_HPP

#include <cstdint>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace hcv
{
	class FDTimer
	{
		//// Methods
		public:
			FDTimer(const FDTimer& i_FDTimer);

			FDTimer(const uint8_t& i_seconds_to_sound_alarm = 10, 
					const uint8_t& i_seconds_to_stop_alarm = 10, 
					const uint8_t& i_seconds_to_stop_recording = 10);


			~FDTimer();

			bool IsTimeToSoundAlarm();

			bool IsTimeToStopAlarm(const time_t& = system_clock::to_time_t(system_clock::now()));

			bool IsTimeToStopRecording(const time_t& = system_clock::to_time_t(system_clock::now()));

			void UpdateLastBodyTimers(const time_t& = system_clock::to_time_t(system_clock::now()));

			void UpdateLastBodyLastDetectedTimer(const time_t& = system_clock::to_time_t(system_clock::now()));
		
		//// Data
		private:
			time_t m_last_body_first_detected;
			
			time_t m_last_body_last_detected;

			uint8_t m_seconds_to_sound_alarm;

			uint8_t m_seconds_to_stop_alarm;

			uint8_t m_seconds_to_stop_recording;
	};

} // namespace hcv

#endif // FD_TIMER_HPP
