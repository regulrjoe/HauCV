#ifndef SOUND_CONTROLLER_TESTS_HPP
#define SOUND_CONTROLLER_TESTS_HPP

#include "sound_controller.hpp"
#include "retval.hpp"

#include <gtest/gtest.h>

using namespace hcv;

namespace {

	/////////////////////////////
	///// SOUND CONTROLLER  /////
	/////////////////////////////
	
	// SoundAlarm() & StopAlarm()
//	TEST(SoundControllerTest, SoundAndStopAlarm)
//	{
//		SoundController sound;
//
//		EXPECT_EQ(sound.SoundAlarm(), RetVal::OK);
//		EXPECT_TRUE(sound.IsAlarmOn());
//
//		EXPECT_EQ(sound.SoundAlarm(), RetVal::NOTOK); // Alarm is already sounding.
//		EXPECT_TRUE(sound.IsAlarmOn());
//
//		EXPECT_EQ(sound.StopAlarm(), RetVal::OK);
//		EXPECT_FALSE(sound.IsAlarmOn());
//
//		EXPECT_EQ(sound.StopAlarm(), RetVal::NOTOK); // Alarm is already off.
//		EXPECT_FALSE(sound.IsAlarmOn());
//
//		EXPECT_EQ(sound.SoundAlarm(), RetVal::OK);
//		EXPECT_TRUE(sound.IsAlarmOn());
//
//		EXPECT_EQ(sound.StopAlarm(), RetVal::OK);
//		EXPECT_FALSE(sound.IsAlarmOn());
//	}
	
	// SoundAlert().
//	TEST(SoundControllerTest, SoundAlert)
//	{
//		SoundController sound;
//
//		EXPECT_EQ(sound.SoundAlert(), RetVal::OK);
//	}

} // namespace

#endif // SOUND_CONTROLLER_TESTS_HPP
