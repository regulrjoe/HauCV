#include "srv/builder.hpp"

#include "srv/states.hpp"
#include "srv/timer.hpp"

#include "soundcontroller/sound_controller.hpp"

#include "motion_detector.hpp"
#include "macros.hpp"

#include <zmq.hpp>

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
				const uint8_t& i_seconds_to_stop_recording,
				const uint16_t& i_motion_detector_min_area,
				const string& i_alarm_soundfile,
				const string& i_alert_soundfile
				)
		{
			PRINT("Building Alert System.");

			MotionDetector* motion_detector = new MotionDetector();
			motion_detector->SetMinimumArea(i_motion_detector_min_area);

			SRVTimer* timer = new SRVTimer(
					i_seconds_to_sound_alarm,
					i_seconds_to_stop_alarm,
					i_seconds_to_stop_recording
					);

			SoundController* sound_ctrl_ptr = new SoundController(
					i_alarm_soundfile,
					i_alert_soundfile
					);

			return new SRVSystem(
					motion_detector,
					timer,
					AlertState::InstanceAsBase(),
					sound_ctrl_ptr
					);
		}

		///////////////////////////
		SRVSystem* SRVBuilder::BuildIdle(
				const uint8_t& i_seconds_to_sound_alarm,
				const uint8_t& i_seconds_to_stop_alarm,
				const uint8_t& i_seconds_to_stop_recording,
				const uint16_t& i_motion_detector_min_area,
				const string& i_alarm_soundfile,
				const string& i_alert_soundfile
				)
		{
			PRINT("Building Idle System.");

			MotionDetector* motion_detector = new MotionDetector();
			motion_detector->SetMinimumArea(i_motion_detector_min_area);

			SRVTimer* timer = new SRVTimer(
					i_seconds_to_sound_alarm,
					i_seconds_to_stop_alarm,
					i_seconds_to_stop_recording
					);

			SoundController* sound_ctrl_ptr = new SoundController(
					i_alarm_soundfile,
					i_alert_soundfile
					);

			return new SRVSystem(
					motion_detector,
					timer,
					IdleState::InstanceAsBase(),
					sound_ctrl_ptr
					);
		}
	} // namespace srv
} // namespace hcv
