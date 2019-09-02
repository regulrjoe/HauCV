#include "srv/timer.hpp"
#include "macros.hpp"

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
			m_last_body_first_detected(i_SRVTimer.m_last_body_first_detected),
			m_last_body_last_detected(i_SRVTimer.m_last_body_last_detected)
		{
			PRINT("SRVTimer constructed by copy.");
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
			this->UpdateLastBodyTimers();

			PRINT("SRVTimer constructed with parameters.");
		}
		
		////////////////////
		SRVTimer::~SRVTimer()
		{
			PRINT("SRVTimer destroyed.");
		}

		////////////////////
		bool SRVTimer::IsTimeToSoundAlarm()
		{
			if (m_last_body_last_detected - m_last_body_first_detected >= m_seconds_to_sound_alarm)
				return true;
			else
				return false;
		}


		////////////////////
		bool SRVTimer::IsTimeToStopAlarm(const time_t& i_time /* = system_clock::to_time_t(system_clock::now()) */)
		{
			if(i_time - m_last_body_last_detected >= m_seconds_to_stop_alarm)
				return true;
			else
				return false;
		}

		////////////////////
		bool SRVTimer::IsTimeToStopRecording(const time_t& i_time /* = system_clock::to_time_t(system_clock::now()) */)
		{
			if(i_time - m_last_body_last_detected >= m_seconds_to_stop_recording)
				return true;
			else
				return false;
		}

		////////////////////
		void SRVTimer::UpdateLastBodyTimers(const time_t& i_time /* = system_clock::to_time_t(system_clock::now()) */)
		{
			m_last_body_first_detected = m_last_body_last_detected = i_time;

			PRINT("SRVTimer: Last body timers updated to: " << ctime(&m_last_body_first_detected));
		}

		////////////////////
		void SRVTimer::UpdateLastBodyLastDetectedTimer(const time_t& i_time /* = system_clock::to_time_t(system_clock::now()) */)
		{
			m_last_body_last_detected = i_time;

			PRINT("SRVTimer: Last body last detected timer updated to: " << ctime(&m_last_body_last_detected));
		}

	} // namespace srv
} // namespace hcv
