#include "fd_timers.hpp"

#include <gtest/gtest.h>

#include <chrono>
#include <thread>

using namespace hcv;

namespace {

	//// Test FDTimers.

	// IsTimeToTriggerAlarm().
	TEST(FDTimersTest, IsTimeToTriggerAlarm)
	{
		/*
		 * TRUE: when FDTimers.last_body_last_detected - last_body_first_detected >= seconds_for_starting_alarm
		 * FALSE: Otherwise.
		 */
		FDTimers timers(1);
		EXPECT_FALSE(timers.IsTimeToTriggerAlarm());

		std::this_thread::sleep_for(std::chrono::seconds(2));
		timers.UpdateLastBodyLastDetectedTimer();

		EXPECT_TRUE(timers.IsTimeToTriggerAlarm());
	}

} // namespace

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
