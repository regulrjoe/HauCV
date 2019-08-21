#include "fd_system.hpp"

#include <iostream>

using namespace std;

namespace hcv
{
	///////////////////////////
	FDSystem::FDSystem(BodyDetector* const i_bd,
			IFDBaseState* const i_bs,
			const uint8_t&  i_seconds_for_starting_alarm,
			const uint8_t& i_seconds_for_stopping_alarm,
			const uint8_t& i_seconds_for_stopping_recording) :
		m_body_detector(i_bd),
		m_base_system_state(i_bs),
		m_current_system_state(i_bs),
		m_seconds_for_starting_alarm(i_seconds_for_starting_alarm),
		m_seconds_for_stopping_alarm(i_seconds_for_stopping_alarm),
		m_seconds_for_stopping_recording(i_seconds_for_stopping_recording)
	{
		cout << "FDSystem constructed." << endl;
	}

	///////////////////////////
	FDSystem::~FDSystem()
	{
		delete m_body_detector;
		delete m_base_system_state;
		delete m_current_system_state;

		cout << "FDSystem destroyed." << endl;
	}

} // namespace hcv
