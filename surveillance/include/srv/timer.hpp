#ifndef SRV_TIMER_HPP
#define SRV_TIMER_HPP

#include <chrono>
#include <cstdint>
#include <ctime>
#include <utility>

using namespace std;
using namespace std::chrono;

namespace hcv
{
	namespace srv
	{
		class SRVTimer
		{
			//// Methods
			public:
				SRVTimer(const SRVTimer& i_SRVTimer);

				SRVTimer(const uint8_t& i_seconds_to_sound_alarm = 10, 
						const uint8_t& i_seconds_to_stop_alarm = 10, 
						const uint8_t& i_seconds_to_stop_recording = 10);


				~SRVTimer();

				bool IsTimeToSoundAlarm();

				bool IsTimeToStopAlarm(const time_t& = system_clock::to_time_t(system_clock::now()));

				bool IsTimeToStopRecording(const time_t& = system_clock::to_time_t(system_clock::now()));

				void UpdateMotionTimestamps(const time_t& = system_clock::to_time_t(system_clock::now()));

				void UpdateLastMotionTimestamp(const time_t& = system_clock::to_time_t(system_clock::now()));
			
			//// Data
			private:
				pair<time_t, time_t> m_motion_timestamps;

				uint8_t m_seconds_to_sound_alarm;

				uint8_t m_seconds_to_stop_alarm;

				uint8_t m_seconds_to_stop_recording;
		};

	} // namespace srv
} // namespace hcv

#endif // SRV_TIMER_HPP
