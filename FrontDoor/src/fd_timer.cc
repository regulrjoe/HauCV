#include "fd_timer.hpp"
#include "macros.hpp"

#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;


namespace hcv
{

	////////////////////
	FDTimer::FDTimer(const FDTimer& i_FDTimer) :
		m_seconds_to_sound_alarm(i_FDTimer.m_seconds_to_sound_alarm),
		m_seconds_to_stop_alarm(i_FDTimer.m_seconds_to_stop_alarm),
		m_seconds_to_stop_recording(i_FDTimer.m_seconds_to_stop_recording),
		m_last_body_first_detected(i_FDTimer.m_last_body_first_detected),
		m_last_body_last_detected(i_FDTimer.m_last_body_last_detected)
	{
		PRINT("FDTimer constructed by copy.");
	}

	////////////////////
	FDTimer::FDTimer(
			const uint8_t& i_seconds_to_sound_alarm /* = 10 */,
			const uint8_t& i_seconds_to_stop_alarm /* = 10 */,
			const uint8_t& i_seconds_to_stop_recording /* = 10 */
			) : 
		m_seconds_to_sound_alarm(i_seconds_to_sound_alarm),
		m_seconds_to_stop_alarm(i_seconds_to_stop_alarm),
		m_seconds_to_stop_recording(i_seconds_to_stop_recording)
	{
		this->UpdateLastBodyTimers();

		PRINT("FDTimer constructed with parameters.");
	}
	
	////////////////////
	FDTimer::~FDTimer()
	{
		PRINT("FDTimer destroyed.");
	}

	////////////////////
	bool FDTimer::IsTimeToSoundAlarm()
	{
		if (m_last_body_last_detected - m_last_body_first_detected >= m_seconds_to_sound_alarm)
			return true;
		else
			return false;
	}


	////////////////////
	bool FDTimer::IsTimeToStopAlarm(const time_t& i_time /* = system_clock::to_time_t(system_clock::now()) */)
	{
		if(i_time - m_last_body_last_detected >= m_seconds_to_stop_alarm)
			return true;
		else
			return false;
	}

	////////////////////
	bool FDTimer::IsTimeToStopRecording(const time_t& i_time /* = system_clock::to_time_t(system_clock::now()) */)
	{
		if(i_time - m_last_body_last_detected >= m_seconds_to_stop_recording)
			return true;
		else
			return false;
	}

	////////////////////
	void FDTimer::UpdateLastBodyTimers(const time_t& i_time /* = system_clock::to_time_t(system_clock::now()) */)
	{
		m_last_body_first_detected = m_last_body_last_detected = i_time;

		PRINT("FDTimer: Last body timers updated to: " << ctime(&m_last_body_first_detected));
	}

	////////////////////
	void FDTimer::UpdateLastBodyLastDetectedTimer(const time_t& i_time /* = system_clock::to_time_t(system_clock::now()) */)
	{
		m_last_body_last_detected = i_time;

		PRINT("FDTimer: Last body last detected timer updated to: " << ctime(&m_last_body_last_detected));
	}

} // namespace hcv
