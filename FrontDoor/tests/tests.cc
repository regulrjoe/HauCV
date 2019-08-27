#include "body_detector.hpp"
#include "fd_timer.hpp"
#include "notifier.hpp"
#include "retval.hpp"
#include "sound_controller.hpp"
#include "video_recorder.hpp"

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include <chrono>
#include <thread>

using namespace cv;
using namespace hcv;
using namespace std;
using namespace std::chrono;

namespace {

	/////////////////////////////
	/////// BODY DETECTOR  //////
	/////////////////////////////

	// DetectBody() On Image in Color with Body.
	TEST(BodyDetectorTest, ImageWithBodyInColor)
	{
		Mat image_body1 = imread("./img/body1.jpg", IMREAD_COLOR);
		Mat image_body2 = imread("./img/body2.jpg", IMREAD_COLOR);
		Mat image_body3 = imread("./img/body3.jpg", IMREAD_COLOR);

		assert(image_body1.data != 0);
		assert(image_body2.data != 0);
		assert(image_body3.data != 0);

		BodyDetector detector;

		EXPECT_TRUE(detector.DetectBody(image_body1));
		EXPECT_TRUE(detector.DetectBody(image_body2));
		EXPECT_TRUE(detector.DetectBody(image_body3));
	}
	
	// DetectBody() On Image in Grayscale with Body.
	TEST(BodyDetectorTest, ImageWithBodyInGrayscale)
	{
		Mat image_body_ir1 = imread("./img/body-ir1.jpg", IMREAD_GRAYSCALE);
		Mat image_body1 = imread("./img/body1.jpg", IMREAD_GRAYSCALE);
		Mat image_body2 = imread("./img/body2.jpg", IMREAD_GRAYSCALE);
		Mat image_body3 = imread("./img/body3.jpg", IMREAD_GRAYSCALE);

		assert(image_body_ir1.data != 0);
		assert(image_body1.data != 0);
		assert(image_body2.data != 0);
		assert(image_body3.data != 0);

		BodyDetector detector;

		EXPECT_TRUE(detector.DetectBody(image_body_ir1));
		EXPECT_TRUE(detector.DetectBody(image_body1));
		EXPECT_TRUE(detector.DetectBody(image_body2));
		EXPECT_TRUE(detector.DetectBody(image_body3));
	}

	// DetectBody() On Image in Color without Body.
	TEST(BodyDetectorTest, ImageWithoutBodyInColor)
	{
		Mat image_nobody1 = imread("./img/nobody1.jpg", IMREAD_COLOR);
		Mat image_nobody2 = imread("./img/nobody2.jpg", IMREAD_COLOR);

		assert(image_nobody1.data != 0);
		assert(image_nobody2.data != 0);

		BodyDetector detector;

		EXPECT_FALSE(detector.DetectBody(image_nobody1));
		EXPECT_FALSE(detector.DetectBody(image_nobody2));
	}
	
	// DetectBody() On Image in Grayscale without Body.
	TEST(BodyDetectorTest, ImageWithoutBodyInGrayscale)
	{
		Mat image_nobody1 = imread("./img/nobody1.jpg", IMREAD_GRAYSCALE);
		Mat image_nobody2 = imread("./img/nobody2.jpg", IMREAD_GRAYSCALE);

		assert(image_nobody1.data != 0);
		assert(image_nobody2.data != 0);

		BodyDetector detector;

		EXPECT_FALSE(detector.DetectBody(image_nobody1));
		EXPECT_FALSE(detector.DetectBody(image_nobody2));
	}

	/////////////////////////////
	///////// FD TIMER //////////
	/////////////////////////////

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
		/*
		 * TRUE: When i_time - FDTimer.m_last_body_last_detected >= FDTimer.m_seconds_to_stop_recording
		 * FALSE: Otherwise.
		 */

		FDTimer timer(0 /*seconds_to_sound_alarm*/,
				1 /*seconds_to_stop_alarm*/,
				1 /*seconds_to_stop_recording*/);

		EXPECT_FALSE(timer.IsTimeToStopRecording());

		timer.UpdateLastBodyTimers(system_clock::to_time_t(system_clock::now()) - 1);
		EXPECT_TRUE(timer.IsTimeToStopRecording());

		timer.UpdateLastBodyTimers();
		EXPECT_FALSE(timer.IsTimeToStopRecording());
	}

	//////////////////////
	////// NOTIFIER //////
	//////////////////////

	// AddDestination() & GetDestination().
	TEST(NotifierTest, AddAndGetDestination)
	{
		Notifier notifier;
		string tmp;

		EXPECT_EQ(notifier.AddDestination("Destination"), RetVal::OK);
		EXPECT_EQ(notifier.GetDestination(0, &tmp), RetVal::OK);
		EXPECT_EQ(tmp, "Destination");
		EXPECT_EQ(notifier.AddDestination(""), RetVal::NOTOK);
		EXPECT_EQ(notifier.GetDestination(1, &tmp), RetVal::NOTOK);
	}

	// NotifyAlarm()
	TEST(NotifierTest, NotifyAlarm)
	{
		Notifier notifier;

		EXPECT_EQ(
				notifier.NotifyAlarm(
					system_clock::to_time_t(
						system_clock::now())),
				RetVal::OK);

	}

	// NotifyAlert()
	TEST(NotifierTest, NotifyAlert)
	{
		Notifier notifier;

		EXPECT_EQ(
				notifier.NotifyAlert(
					system_clock::to_time_t(
						system_clock::now())),
				RetVal::OK);
	}

	/////////////////////////////
	///// SOUND CONTROLLER  /////
	/////////////////////////////
	
	// SoundAlarm() & StopAlarm()
	TEST(SoundControllerTest, SoundAndStopAlarm)
	{
		SoundController sound;

		EXPECT_EQ(sound.SoundAlarm(), RetVal::OK);
		EXPECT_TRUE(sound.IsAlarmOn());

		EXPECT_EQ(sound.SoundAlarm(), RetVal::NOTOK); // Alarm is already sounding.
		EXPECT_TRUE(sound.IsAlarmOn());

		EXPECT_EQ(sound.StopAlarm(), RetVal::OK);
		EXPECT_FALSE(sound.IsAlarmOn());

		EXPECT_EQ(sound.StopAlarm(), RetVal::NOTOK); // Alarm is already off.
		EXPECT_FALSE(sound.IsAlarmOn());

		EXPECT_EQ(sound.SoundAlarm(), RetVal::OK);
		EXPECT_TRUE(sound.IsAlarmOn());

		EXPECT_EQ(sound.StopAlarm(), RetVal::OK);
		EXPECT_FALSE(sound.IsAlarmOn());
	}
	
	// SoundAlert().
	TEST(SoundControllerTest, SoundAlert)
	{
		SoundController sound;

		EXPECT_EQ(sound.SoundAlert(), RetVal::OK);
	}

	/////////////////////////////
	////// VIDEO RECORDER  //////
	/////////////////////////////

	// Start() and Stop().
	TEST(VideoRecorderTest, StartAndStopRecording)
	{
		VideoRecorder recorder;

		EXPECT_EQ(recorder.Start(), RetVal::OK);
		EXPECT_TRUE(recorder.IsRecording());

		EXPECT_EQ(recorder.Start(), RetVal::NOTOK); // Already recording.
		EXPECT_TRUE(recorder.IsRecording());

		EXPECT_EQ(recorder.Stop(), RetVal::OK);
		EXPECT_FALSE(recorder.IsRecording());

		EXPECT_EQ(recorder.Stop(), RetVal::NOTOK); // Already stopped.
		EXPECT_FALSE(recorder.IsRecording());

		EXPECT_EQ(recorder.Start(), RetVal::OK);
		EXPECT_TRUE(recorder.IsRecording());

		EXPECT_EQ(recorder.Stop(), RetVal::OK);
		EXPECT_FALSE(recorder.IsRecording());
	}

	// Store().
	TEST(VideoRecorderTest, StoreRecording)
	{
		VideoRecorder recorder;

		EXPECT_EQ(recorder.Store(), RetVal::NOTOK); // No video to store.
		recorder.Start();
		recorder.Stop();
		EXPECT_EQ(recorder.Store(), RetVal::OK);

		EXPECT_EQ(recorder.Store(), RetVal::NOTOK); // No video to store.
	}

} // namespace

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
