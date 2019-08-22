#include "fd_timers.hpp"

#include <gtest/gtest.h>

#include <chrono>
#include <thread>

using namespace hcv;

namespace {

	//// Test FDTimers.

	// IsTimeToStartAlarm().
	TEST(FDTimersTest, IsTimeToStartAlarm)
	{
		/*
		 * TRUE: when FDTimers.m_last_body_last_detected - FDTimers.m_last_body_first_detected >= FDTimers.m_seconds_to_start_alarm
		 * FALSE: Otherwise.
		 */

		FDTimers timers(1 /*seconds_to_start_alarm*/);

		EXPECT_FALSE(timers.IsTimeToStartAlarm());

		std::this_thread::sleep_for(std::chrono::seconds(1));
		timers.UpdateLastBodyLastDetectedTimer();

		EXPECT_TRUE(timers.IsTimeToStartAlarm());

		timers.UpdateLastBodyTimers();

		EXPECT_FALSE(timers.IsTimeToStartAlarm());
	}

	// IsTimeToStopAlarm().
	TEST(FDTimersTest, IsTimeToStopAlarm)
	{
		/*
		 * TRUE: when Now - FDTimers.m_last_body_last_detected >= FDTimers.m_seconds_to_stop_alarm
		 * FALSE: Otherwise.
		 */

		FDTimers timers(0 /*seconds_to_start_alarm*/, 
				1 /*seconds_to_stop_alarm*/);

		EXPECT_FALSE(timers.IsTimeToStopAlarm());

		std::this_thread::sleep_for(std::chrono::seconds(1));

		EXPECT_TRUE(timers.IsTimeToStopAlarm());

		timers.UpdateLastBodyTimers();

		EXPECT_FALSE(timers.IsTimeToStopAlarm());

		std::this_thread::sleep_for(std::chrono::seconds(1));

		EXPECT_TRUE(timers.IsTimeToStopAlarm());
	}

	// IsTimeToStopRecording().
	TEST(FDTimersTest, IsTimeToStopRecording)
	{
		FDTimers timers(0 /*seconds_to_start_alarm*/,
				1 /*seconds_to_stop_alarm*/,
				1 /*seconds_to_stop_recording*/);

		EXPECT_FALSE(timers.IsTimeToStopRecording());

		std::this_thread::sleep_for(std::chrono::seconds(1));

		EXPECT_TRUE(timers.IsTimeToStopRecording());

		timers.UpdateLastBodyTimers();

		EXPECT_FALSE(timers.IsTimeToStopRecording());

		std::this_thread::sleep_for(std::chrono::seconds(1));

		EXPECT_TRUE(timers.IsTimeToStopRecording());
	}

} // namespace

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
