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
		m_seconds_for_starting_alarm(i_FDTimers.m_seconds_for_starting_alarm),
		m_seconds_for_stopping_alarm(i_FDTimers.m_seconds_for_stopping_alarm),
		m_seconds_for_stopping_recording(i_FDTimers.m_seconds_for_stopping_recording),
		m_last_body_first_detected(i_FDTimers.m_last_body_first_detected),
		m_last_body_last_detected(i_FDTimers.m_last_body_last_detected)
	{
		PRINT("FDTimer constructed by copy.");
	}

	////////////////////
	FDTimers::FDTimers(
			const uint8_t& i_seconds_for_starting_alarm /* = 10 */,
			const uint8_t& i_seconds_for_stopping_alarm /* = 10 */,
			const uint8_t& i_seconds_for_stopping_recording /* = 10 */
			) : 
		m_seconds_for_starting_alarm(i_seconds_for_starting_alarm),
		m_seconds_for_stopping_alarm(i_seconds_for_stopping_alarm),
		m_seconds_for_stopping_recording(i_seconds_for_stopping_recording)
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
	bool FDTimers::IsTimeToTriggerAlarm()
	{
		if (m_last_body_last_detected - m_last_body_first_detected >= m_seconds_for_starting_alarm)
			return true;
		else
			return false;
	}


	////////////////////
	bool FDTimers::IsTimeToStopAlarm()
	{
		return false;
	}

	////////////////////
	bool FDTimers::IsTimeToStopRecording()
	{
		return false;
	}

} // namespace hcv
