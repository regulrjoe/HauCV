#include "fd_timers.hpp"

#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

#ifndef NDEBUG
#define PRINT(to_print) cout << to_print << endl
#else
#define PRINT(to_print) while(0) // Avoid empty statements.
#endif

namespace hcv
{

	////////////////////
	FDTimers::FDTimers(const FDTimers& i_FDTimers) :
		m_seconds_to_sound_alarm(i_FDTimers.m_seconds_to_sound_alarm),
		m_seconds_to_stop_alarm(i_FDTimers.m_seconds_to_stop_alarm),
		m_seconds_to_stop_recording(i_FDTimers.m_seconds_to_stop_recording),
		m_last_body_first_detected(i_FDTimers.m_last_body_first_detected),
		m_last_body_last_detected(i_FDTimers.m_last_body_last_detected)
	{
		PRINT("FDTimer constructed by copy.");
	}

	////////////////////
	FDTimers::FDTimers(
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
	FDTimers::~FDTimers()
	{
		PRINT("FDTimer destroyed.");
	}

	////////////////////
	void FDTimers::UpdateLastBodyTimers()
	{
		m_last_body_first_detected = m_last_body_last_detected = system_clock::to_time_t(system_clock::now());

		PRINT("FDTimer: Last body timers updated to: " << ctime(&m_last_body_first_detected));
	}

	////////////////////
	void FDTimers::UpdateLastBodyLastDetectedTimer()
	{
		m_last_body_last_detected = system_clock::to_time_t(system_clock::now());

		PRINT("FDTimer: Last body last detected timer updated to: " << ctime(&m_last_body_last_detected));
	}

	////////////////////
	bool FDTimers::IsTimeToSoundAlarm()
	{
		if (m_last_body_last_detected - m_last_body_first_detected >= m_seconds_to_sound_alarm)
			return true;
		else
			return false;
	}


	////////////////////
	bool FDTimers::IsTimeToStopAlarm()
	{
		if(system_clock::to_time_t(system_clock::now()) - m_last_body_last_detected >= m_seconds_to_stop_alarm)
			return true;
		else
			return false;
	}

	////////////////////
	bool FDTimers::IsTimeToStopRecording()
	{
		if(system_clock::to_time_t(system_clock::now()) - m_last_body_last_detected >= m_seconds_to_stop_recording)
			return true;
		else
			return false;
	}

} // namespace hcv
