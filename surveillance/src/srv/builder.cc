#include "srv/builder.hpp"

#include "srv/state.hpp"
#include "srv/timer.hpp"

#include "body_detector.hpp"
#include "macros.hpp"
#include "notifier.hpp"

#include <iostream>

using namespace std;

namespace hcv
{
	namespace srv
	{
		///////////////////////////
		SRVSystem* SRVBuilder::BuildAlert(
				const uint8_t& i_seconds_to_sound_alarm,
				const uint8_t& i_seconds_to_stop_alarm,
				const uint8_t& i_seconds_to_stop_recording
				)
		{
			PRINT("Building Alert System.");

			BodyDetector* body_detector = new BodyDetector();

			Notifier* notifier = new Notifier();

			SRVTimer* timer = new SRVTimer(
						i_seconds_to_sound_alarm,
						i_seconds_to_stop_alarm,
						i_seconds_to_stop_recording
					);

			return new SRVSystem(
					body_detector,
					timer,
					AlertState::InstanceAsBase(),
					notifier
					);
		}

		///////////////////////////
		SRVSystem* SRVBuilder::BuildIdle(
				const uint8_t& i_seconds_to_sound_alarm,
				const uint8_t& i_seconds_to_stop_alarm,
				const uint8_t& i_seconds_to_stop_recording
				)
		{
			PRINT("Building Idle System.");

			BodyDetector* body_detector = new BodyDetector();

			Notifier* notifier = new Notifier();

			SRVTimer* timer = new SRVTimer(
						i_seconds_to_sound_alarm,
						i_seconds_to_stop_alarm,
						i_seconds_to_stop_recording
					);
			return new SRVSystem(
					body_detector,
					timer,
					IdleState::InstanceAsBase(),
					notifier
					);
		}

	} // namespace srv
} // namespace hcv
