#ifndef ASV_TIMER_TESTS_HPP
#define ASV_TIMER_TESTS_HPP

#include "asv_timer.hpp"
#include "retval.hpp"

#include <gtest/gtest.h>

using namespace hcv;
using namespace hcv::asv;
using namespace std;
using namespace std::chrono;

namespace {

	/////////////////////////////
	///////// ASV TIMER //////////
	/////////////////////////////

	// IsTimeToSoundAlarm().
	TEST(ASVTimerTest, IsTimeToSoundAlarm)
	{
		/*
		 * TRUE: When ASVTimer.m_last_body_last_detected - ASVTimer.m_last_body_first_detected >= ASVTimer.m_seconds_to_sound_alarm
		 * FALSE: Otherwise.
		 */

		ASVTimer timer(1 /*seconds_to_sound_alarm*/);

		EXPECT_FALSE(timer.IsTimeToSoundAlarm());

		timer.UpdateLastBodyLastDetectedTimer(system_clock::to_time_t(system_clock::now()) + 1);
		EXPECT_TRUE(timer.IsTimeToSoundAlarm());

		timer.UpdateLastBodyTimers();
		EXPECT_FALSE(timer.IsTimeToSoundAlarm());
	}

	// IsTimeToStopAlarm().
	TEST(ASVTimerTest, IsTimeToStopAlarm)
	{
		/*
		 * TRUE: When i_time - ASVTimer.m_last_body_last_detected >= ASVTimer.m_seconds_to_stop_alarm
		 * FALSE: Otherwise.
		 */

		ASVTimer timer(0 /*seconds_to_sound_alarm*/, 
				1 /*seconds_to_stop_alarm*/);

		EXPECT_FALSE(timer.IsTimeToStopAlarm());

		timer.UpdateLastBodyTimers(system_clock::to_time_t(system_clock::now()) - 1);
		EXPECT_TRUE(timer.IsTimeToStopAlarm());

		timer.UpdateLastBodyTimers();
		EXPECT_FALSE(timer.IsTimeToStopAlarm());
	}

	// IsTimeToStopRecording().
	TEST(ASVTimerTest, IsTimeToStopRecording)
	{
		/*
		 * TRUE: When i_time - ASVTimer.m_last_body_last_detected >= ASVTimer.m_seconds_to_stop_recording
		 * FALSE: Otherwise.
		 */

		ASVTimer timer(0 /*seconds_to_sound_alarm*/,
				1 /*seconds_to_stop_alarm*/,
				1 /*seconds_to_stop_recording*/);

		EXPECT_FALSE(timer.IsTimeToStopRecording());

		timer.UpdateLastBodyTimers(system_clock::to_time_t(system_clock::now()) - 1);
		EXPECT_TRUE(timer.IsTimeToStopRecording());

		timer.UpdateLastBodyTimers();
		EXPECT_FALSE(timer.IsTimeToStopRecording());
	}

} // namespace

#endif // ASV_TIMER_TESTS_HPP
