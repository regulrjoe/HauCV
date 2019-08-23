#include "fd_timer.hpp"

#include <gtest/gtest.h>

#include <chrono>
#include <thread>

using namespace hcv;
using namespace std;
using namespace std::chrono;

namespace {

	//// Test FDTimer.

	// IsTimeToSoundAlarm().
	TEST(FDTimerTest, IsTimeToSoundAlarm)
	{
		/*
		 * TRUE: When FDTimer.m_last_body_last_detected - FDTimer.m_last_body_first_detected >= FDTimer.m_seconds_to_sound_alarm
		 * FALSE: Otherwise.
		 */

		FDTimer timer(1 /*seconds_to_sound_alarm*/);

		EXPECT_FALSE(timer.IsTimeToSoundAlarm());

		timer.UpdateLastBodyLastDetectedTimer(system_clock::to_time_t(system_clock::now()) + 1);

		EXPECT_TRUE(timer.IsTimeToSoundAlarm());

		timer.UpdateLastBodyTimers();

		EXPECT_FALSE(timer.IsTimeToSoundAlarm());
	}

	// IsTimeToStopAlarm().
	TEST(FDTimerTest, IsTimeToStopAlarm)
	{
		/*
		 * TRUE: When i_time - FDTimer.m_last_body_last_detected >= FDTimer.m_seconds_to_stop_alarm
		 * FALSE: Otherwise.
		 */

		FDTimer timer(0 /*seconds_to_sound_alarm*/, 
				1 /*seconds_to_stop_alarm*/);

		EXPECT_FALSE(timer.IsTimeToStopAlarm());

		timer.UpdateLastBodyTimers(system_clock::to_time_t(system_clock::now()) - 1);

		EXPECT_TRUE(timer.IsTimeToStopAlarm());

		timer.UpdateLastBodyTimers();

		EXPECT_FALSE(timer.IsTimeToStopAlarm());
	}

	// IsTimeToStopRecording().
	TEST(FDTimerTest, IsTimeToStopRecording)
	{
		FDTimer timer(0 /*seconds_to_sound_alarm*/,
				1 /*seconds_to_stop_alarm*/,
				1 /*seconds_to_stop_recording*/);

		EXPECT_FALSE(timer.IsTimeToStopRecording());

		timer.UpdateLastBodyTimers(system_clock::to_time_t(system_clock::now()) - 1);

		EXPECT_TRUE(timer.IsTimeToStopRecording());

		timer.UpdateLastBodyTimers();

		EXPECT_FALSE(timer.IsTimeToStopRecording());
	}

} // namespace

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
