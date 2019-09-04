#ifndef MOTION_DETECTOR_TESTS_HPP
#define MOTION_DETECTOR_TESTS_HPP

#include "motion_detector.hpp"

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include <cstdint>

using namespace cv;
using namespace hcv;

namespace {

	/////////////////////////////
	/////// MOTION DETECTOR  //////
	/////////////////////////////

	// DetectMotion() On Image with a body.
	TEST(DetectMotionTest, ImageWithBody)
	{
		Mat base_image = imread("/app/tests/img/B_base.jpg", IMREAD_GRAYSCALE);
		Mat test_body = imread("/app/tests/img/B_body1.jpg", IMREAD_GRAYSCALE);

		assert(base_image.data != 0);
		assert(test_body.data != 0);

		MotionDetector detector(base_image, 10000);

		EXPECT_TRUE(detector.DetectMotion(test_body));
		sleep(1);
	}
	
	// DetectMotion() On Image with a body and noise
	TEST(DetectMotionTest, ImageWithBodyAndNoise)
	{
		Mat base_image = imread("/app/tests/img/B_base.jpg", IMREAD_GRAYSCALE);
		Mat test_body_noise = imread("/app/tests/img/B_body_noise1.jpg", IMREAD_GRAYSCALE);

		assert(base_image.data != 0);
		assert(test_body_noise.data != 0);

		MotionDetector detector(base_image, 10000);

		EXPECT_TRUE(detector.DetectMotion(test_body_noise));
		sleep(1);
	}

	// DetectMotion() On Image with only noise
	TEST(DetectMotionTest, ImageWithNoise)
	{
		Mat base_image = imread("/app/tests/img/B_base.jpg", IMREAD_GRAYSCALE);
		Mat test_noise = imread("/app/tests/img/B_noise1.jpg", IMREAD_GRAYSCALE);

		assert(base_image.data != 0);
		assert(test_noise.data != 0);

		MotionDetector detector(base_image, 10000);

		EXPECT_FALSE(detector.DetectMotion(test_noise));
	}

} // namespace

#endif // MOTION_DETECTOR_TESTS_HPP
