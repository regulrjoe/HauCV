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
		Mat base_img = imread("/app/tests/img/B_base.jpg", IMREAD_GRAYSCALE);
		Mat body_img = imread("/app/tests/img/B_body1.jpg", IMREAD_GRAYSCALE);

		assert(base_img.data != 0);
		assert(body_img.data != 0);

		cv::resize(base_img, base_img, cv::Size(), 0.5, 0.5);
		cv::resize(body_img, body_img, cv::Size(), 0.5, 0.5);

		MotionDetector detector(base_img, 500);

		EXPECT_TRUE(detector.DetectMotion(body_img));
		sleep(1);
	}
	
	// DetectMotion() On Image with a body and noise
	TEST(DetectMotionTest, ImageWithBodyAndNoise)
	{
		Mat base_img = imread("/app/tests/img/B_base.jpg", IMREAD_GRAYSCALE);
		Mat body_noise_img = imread("/app/tests/img/B_body_noise1.jpg", IMREAD_GRAYSCALE);

		assert(base_img.data != 0);
		assert(body_noise_img.data != 0);

		cv::resize(base_img, base_img, cv::Size(), 0.5, 0.5);
		cv::resize(body_noise_img, body_noise_img, cv::Size(), 0.5, 0.5);

		MotionDetector detector(base_img, 500);

		EXPECT_TRUE(detector.DetectMotion(body_noise_img));
		sleep(1);
	}

	// DetectMotion() On Image with only noise
	TEST(DetectMotionTest, ImageWithNoise)
	{
		Mat base_img = imread("/app/tests/img/B_base.jpg", IMREAD_GRAYSCALE);
		Mat noise_img = imread("/app/tests/img/B_noise1.jpg", IMREAD_GRAYSCALE);

		assert(base_img.data != 0);
		assert(noise_img.data != 0);

		cv::resize(base_img, base_img, cv::Size(), 0.5, 0.5);
		cv::resize(noise_img, noise_img, cv::Size(), 0.5, 0.5);

		MotionDetector detector(base_img, 500);

		EXPECT_FALSE(detector.DetectMotion(noise_img));
	}

} // namespace

#endif // MOTION_DETECTOR_TESTS_HPP
