#include "srv/timer.hpp"
#include "utils/macros.hpp"

#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;


namespace hcv
{
	namespace srv
	{
		////////////////////
		SRVTimer::SRVTimer(const SRVTimer& i_SRVTimer) :
			m_seconds_to_sound_alarm(i_SRVTimer.m_seconds_to_sound_alarm),
			m_seconds_to_stop_alarm(i_SRVTimer.m_seconds_to_stop_alarm),
			m_seconds_to_stop_recording(i_SRVTimer.m_seconds_to_stop_recording),
			m_motion_timestamps(i_SRVTimer.m_motion_timestamps)
		{
			printINFO("SRVTimer constructed by copy.");
		}

		////////////////////
		SRVTimer::SRVTimer(
				const uint8_t& i_seconds_to_sound_alarm /* = 10 */,
				const uint8_t& i_seconds_to_stop_alarm /* = 10 */,
				const uint8_t& i_seconds_to_stop_recording /* = 10 */
				) : 
			m_seconds_to_sound_alarm(i_seconds_to_sound_alarm),
			m_seconds_to_stop_alarm(i_seconds_to_stop_alarm),
			m_seconds_to_stop_recording(i_seconds_to_stop_recording)
		{
			this->UpdateMotionTimestamps();

			printINFO("SRVTimer constructed with parameters.");
		}
		
		////////////////////
		SRVTimer::~SRVTimer()
		{
			printINFO("SRVTimer destroyed.");
		}

		////////////////////
		bool SRVTimer::IsTimeToSoundAlarm()
		{
			if (m_motion_timestamps.second - m_motion_timestamps.first >= m_seconds_to_sound_alarm)
				return true;
			else
				return false;
		}


		////////////////////
		bool SRVTimer::IsTimeToStopAlarm(const time_t& i_time /* = system_clock::to_time_t(system_clock::now()) */)
		{
			if(i_time - m_motion_timestamps.second >= m_seconds_to_stop_alarm)
				return true;
			else
				return false;
		}

		////////////////////
		bool SRVTimer::IsTimeToStopRecording(const time_t& i_time /* = system_clock::to_time_t(system_clock::now()) */)
		{
			if(i_time - m_motion_timestamps.second >= m_seconds_to_stop_recording)
				return true;
			else
				return false;
		}

		////////////////////
		void SRVTimer::UpdateMotionTimestamps(const time_t& i_time /* = system_clock::to_time_t(system_clock::now()) */)
		{
			m_motion_timestamps.first = m_motion_timestamps.second = i_time;

			printINFO("Motion timestamps updated to: " << ctime(&m_motion_timestamps.first));
		}

		////////////////////
		void SRVTimer::UpdateLastMotionTimestamp(const time_t& i_time /* = system_clock::to_time_t(system_clock::now()) */)
		{
			m_motion_timestamps.second = i_time;

			printINFO("Last motion timestamp updated to: " << ctime(&m_motion_timestamps.second));
		}

	} // namespace srv
} // namespace hcv
