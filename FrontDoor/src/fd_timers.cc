#include "fd_timers.hpp"

#include <iostream>

using namespace std;

namespace hcv
{

	FDTimers::FDTimers(const FDTimers& i_FDTimers) :
		m_seconds_for_starting_alarm(i_FDTimers.m_seconds_for_starting_alarm),
		m_seconds_for_stopping_alarm(i_FDTimers.m_seconds_for_stopping_alarm),
		m_seconds_for_stopping_recording(i_FDTimers.m_seconds_for_stopping_recording),
		m_last_body_first_detected(i_FDTimers.m_last_body_first_detected),
		m_last_body_last_detected(i_FDTimers.m_last_body_last_detected)
	{
		cout << "FDTimer constructed by copy." << endl;
	}

	FDTimers::FDTimers(
			const uint8_t& i_seconds_for_starting_alarm = 10, 
			const uint8_t& i_seconds_for_stopping_alarm = 10,
			const uint8_t& i_seconds_for_stopping_recording = 10
			) : 
		m_seconds_for_starting_alarm(i_seconds_for_starting_alarm),
		m_seconds_for_stopping_alarm(i_seconds_for_stopping_alarm),
		m_seconds_for_stopping_recording(i_seconds_for_stopping_recording)
	{
		m_last_body_first_detected = 0;
		m_last_body_last_detected = 0;

		cout << "FDTimer constructed with parameters." << endl;
	}

	FDTimers::~FDTimers()
	{
		cout << "FDTimer destroyed." << endl;
	}

} // namespace hcv
