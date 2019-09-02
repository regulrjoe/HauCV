#ifndef SRV_TIMER_TESTS_HPP
#define SRV_TIMER_TESTS_HPP

#include "srv/timer.hpp"
#include "retval.hpp"

#include <gtest/gtest.h>

using namespace hcv;
using namespace hcv::srv;
using namespace std;
using namespace std::chrono;

namespace {

	/////////////////////////////
	///////// SRV TIMER //////////
	/////////////////////////////

	// IsTimeToSoundAlarm().
	TEST(SRVTimerTest, IsTimeToSoundAlarm)
	{
		/*
		 * TRUE: When SRVTimer.m_motion_timestamps.second - SRVTimer.m_motion_timestamps.first >= SRVTimer.m_seconds_to_sound_alarm
		 * FALSE: Otherwise.
		 */

		SRVTimer timer(1 /*seconds_to_sound_alarm*/);

		EXPECT_FALSE(timer.IsTimeToSoundAlarm());

		timer.UpdateLastMotionTimestamp(system_clock::to_time_t(system_clock::now()) + 1);
		EXPECT_TRUE(timer.IsTimeToSoundAlarm());

		timer.UpdateMotionTimestamps();
		EXPECT_FALSE(timer.IsTimeToSoundAlarm());
	}

	// IsTimeToStopAlarm().
	TEST(SRVTimerTest, IsTimeToStopAlarm)
	{
		/*
		 * TRUE: When i_time - SRVTimer.m_motion_timestamps.second >= SRVTimer.m_seconds_to_stop_alarm
		 * FALSE: Otherwise.
		 */

		SRVTimer timer(0 /*seconds_to_sound_alarm*/, 
				1 /*seconds_to_stop_alarm*/);

		EXPECT_FALSE(timer.IsTimeToStopAlarm());

		timer.UpdateMotionTimestamps(system_clock::to_time_t(system_clock::now()) - 1);
		EXPECT_TRUE(timer.IsTimeToStopAlarm());

		timer.UpdateMotionTimestamps();
		EXPECT_FALSE(timer.IsTimeToStopAlarm());
	}

	// IsTimeToStopRecording().
	TEST(SRVTimerTest, IsTimeToStopRecording)
	{
		/*
		 * TRUE: When i_time - SRVTimer.m_motion_timestamps.second >= SRVTimer.m_seconds_to_stop_recording
		 * FALSE: Otherwise.
		 */

		SRVTimer timer(0 /*seconds_to_sound_alarm*/,
				1 /*seconds_to_stop_alarm*/,
				1 /*seconds_to_stop_recording*/);

		EXPECT_FALSE(timer.IsTimeToStopRecording());

		timer.UpdateMotionTimestamps(system_clock::to_time_t(system_clock::now()) - 1);
		EXPECT_TRUE(timer.IsTimeToStopRecording());

		timer.UpdateMotionTimestamps();
		EXPECT_FALSE(timer.IsTimeToStopRecording());
	}

} // namespace

#endif // SRV_TIMER_TESTS_HPP
