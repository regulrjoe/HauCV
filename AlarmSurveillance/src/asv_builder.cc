#include "asv_builder.hpp"

#include "body_detector.hpp"
#include "asv_state.hpp"
#include "asv_timer.hpp"
#include "macros.hpp"
#include "notifier.hpp"

#include <iostream>

using namespace std;

namespace hcv
{
	namespace asv
	{
		///////////////////////////
		ASVSystem* ASVBuilder::BuildAlert(
				const uint8_t& i_seconds_to_sound_alarm,
				const uint8_t& i_seconds_to_stop_alarm,
				const uint8_t& i_seconds_to_stop_recording
				)
		{
			PRINT("Building Alert System.");

			BodyDetector* body_detector = new BodyDetector();

			Notifier* notifier = new Notifier();

			ASVTimer* timer = new ASVTimer(
						i_seconds_to_sound_alarm,
						i_seconds_to_stop_alarm,
						i_seconds_to_stop_recording
					);

			return new ASVSystem(
					body_detector,
					timer,
					AlertState::InstanceAsBase(),
					notifier
					);
		}

		///////////////////////////
		ASVSystem* ASVBuilder::BuildIdle(
				const uint8_t& i_seconds_to_sound_alarm,
				const uint8_t& i_seconds_to_stop_alarm,
				const uint8_t& i_seconds_to_stop_recording
				)
		{
			PRINT("Building Idle System.");

			BodyDetector* body_detector = new BodyDetector();

			Notifier* notifier = new Notifier();

			ASVTimer* timer = new ASVTimer(
						i_seconds_to_sound_alarm,
						i_seconds_to_stop_alarm,
						i_seconds_to_stop_recording
					);
			return new ASVSystem(
					body_detector,
					timer,
					IdleState::InstanceAsBase(),
					notifier
					);
		}

	} // namespace asv
} // namespace hcv
