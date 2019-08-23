#include "fd_builder.hpp"

#include "body_detector.hpp"
#include "fd_state.hpp"
#include "macros.hpp"

#include <iostream>

using namespace std;

namespace hcv
{
	///////////////////////////
	FDSystem* FDBuilder::BuildAlert(
			const uint8_t& i_seconds_for_starting_alarm,
			const uint8_t& i_seconds_for_stopping_alarm,
			const uint8_t& i_seconds_for_stopping_recording
			)
	{
		PRINT("Building Alert System.");

		BodyDetector* body_detector = new BodyDetector();

		FDTimers* timer = new FDTimers(
					i_seconds_for_starting_alarm,
					i_seconds_for_stopping_alarm,
					i_seconds_for_stopping_recording
				);

		return new FDSystem(
				body_detector,
				AlertState::InstanceAsBase(),
				timer
				);
	}

	///////////////////////////
	FDSystem* FDBuilder::BuildIdle(
			const uint8_t& i_seconds_for_starting_alarm,
			const uint8_t& i_seconds_for_stopping_alarm,
			const uint8_t& i_seconds_for_stopping_recording
			)
	{
		PRINT("Building Idle System.");

		BodyDetector* body_detector = new BodyDetector();

		FDTimers* timer = new FDTimers(
					i_seconds_for_starting_alarm,
					i_seconds_for_stopping_alarm,
					i_seconds_for_stopping_recording
				);
		return new FDSystem(
				body_detector,
				IdleState::InstanceAsBase(),
				timer
				);
	}

} // namespace hcv
