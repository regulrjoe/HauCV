#include "fd_builder.hpp"

#include "body_detector.hpp"
#include "fd_state.hpp"
#include "fd_timer.hpp"
#include "macros.hpp"
#include "notifier.hpp"

#include <iostream>

using namespace std;

namespace hcv
{
	///////////////////////////
	FDSystem* FDBuilder::BuildAlert(
			const uint8_t& i_seconds_to_sound_alarm,
			const uint8_t& i_seconds_to_stop_alarm,
			const uint8_t& i_seconds_to_stop_recording
			)
	{
		PRINT("Building Alert System.");

		BodyDetector* body_detector = new BodyDetector();

		Notifier* notifier = new Notifier();

		FDTimer* timer = new FDTimer(
					i_seconds_to_sound_alarm,
					i_seconds_to_stop_alarm,
					i_seconds_to_stop_recording
				);

		return new FDSystem(
				body_detector,
				timer,
				AlertState::InstanceAsBase(),
				notifier
				);
	}

	///////////////////////////
	FDSystem* FDBuilder::BuildIdle(
			const uint8_t& i_seconds_to_sound_alarm,
			const uint8_t& i_seconds_to_stop_alarm,
			const uint8_t& i_seconds_to_stop_recording
			)
	{
		PRINT("Building Idle System.");

		BodyDetector* body_detector = new BodyDetector();

		Notifier* notifier = new Notifier();

		FDTimer* timer = new FDTimer(
					i_seconds_to_sound_alarm,
					i_seconds_to_stop_alarm,
					i_seconds_to_stop_recording
				);
		return new FDSystem(
				body_detector,
				timer,
				IdleState::InstanceAsBase(),
				notifier
				);
	}

} // namespace hcv
