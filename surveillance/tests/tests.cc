#include "motion_detector_tests.hpp"
#include "srv_timer_tests.hpp"
#include "notifier_tests.hpp"
#include "sound_controller_tests.hpp"
#include "video_recorder_tests.hpp"

#include <gtest/gtest.h>

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
