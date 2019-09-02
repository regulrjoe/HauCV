#ifndef MOTION_DETECTOR_TESTS_HPP
#define MOTION_DETECTOR_TESTS_HPP

#include "motion_detector.hpp"

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace hcv;

namespace {

	/////////////////////////////
	/////// MOTION DETECTOR  //////
	/////////////////////////////

	// DetectMotion() On Image in Color with Body.
	TEST(DetectMotionTest, ImageWithBody)
	{
		Mat base_image = imread("./img/1_base.jpg", IMREAD_COLOR);
		Mat test_image1 = imread("./img/1_body1.jpg", IMREAD_COLOR);
		Mat test_image2 = imread("./img/1_body2.jpg", IMREAD_COLOR);

		assert(base_image.data != 0);
		assert(test_image1.data != 0);
		assert(test_image2.data != 0);

		MotionDetector detector;

		EXPECT_TRUE(detector.DetectMotion(test_image1));
		EXPECT_TRUE(detector.DetectMotion(test_image2));
		EXPECT_FALSE(detector.DetectMotion(base_image));
	}

} // namespace

#endif // MOTION_DETECTOR_TESTS_HPP
