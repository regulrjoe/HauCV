#ifndef VIDEO_RECORDER_TESTS_HPP
#define VIDEO_RECORDER_TESTS_HPP

#include "video_recorder.hpp"
#include "retval.hpp"

#include <gtest/gtest.h>

using namespace hcv;

namespace {

	/////////////////////////////
	////// VIDEO RECORDER  //////
	/////////////////////////////

	// Start() and Stop().
//	TEST(VideoRecorderTest, StartAndStopRecording)
//	{
//		VideoRecorder recorder;
//
//		EXPECT_EQ(recorder.Start(), RetVal::OK);
//		EXPECT_TRUE(recorder.IsRecording());
//
//		EXPECT_EQ(recorder.Start(), RetVal::NOTOK); // Already recording.
//		EXPECT_TRUE(recorder.IsRecording());
//
//		EXPECT_EQ(recorder.Stop(), RetVal::OK);
//		EXPECT_FALSE(recorder.IsRecording());
//
//		EXPECT_EQ(recorder.Stop(), RetVal::NOTOK); // Already stopped.
//		EXPECT_FALSE(recorder.IsRecording());
//
//		EXPECT_EQ(recorder.Start(), RetVal::OK);
//		EXPECT_TRUE(recorder.IsRecording());
//
//		EXPECT_EQ(recorder.Stop(), RetVal::OK);
//		EXPECT_FALSE(recorder.IsRecording());
//	}

	// Store().
//	TEST(VideoRecorderTest, StoreRecording)
//	{
//		VideoRecorder recorder;
//
//		EXPECT_EQ(recorder.Store(), RetVal::NOTOK); // No video to store.
//		recorder.Start();
//		recorder.Stop();
//		EXPECT_EQ(recorder.Store(), RetVal::OK);
//
//		EXPECT_EQ(recorder.Store(), RetVal::NOTOK); // No video to store.
//	}

} // namespace

#endif // VIDEO_RECORDER_TESTS_HPP
