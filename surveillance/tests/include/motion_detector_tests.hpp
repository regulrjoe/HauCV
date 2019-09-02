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
//	TEST(BodyDetectorTest, ImageWithBodyInColor)
//	{
//		Mat image_body1 = imread("./img/body1.jpg", IMREAD_COLOR);
//		Mat image_body2 = imread("./img/body2.jpg", IMREAD_COLOR);
//		Mat image_body3 = imread("./img/body3.jpg", IMREAD_COLOR);
//
//		assert(image_body1.data != 0);
//		assert(image_body2.data != 0);
//		assert(image_body3.data != 0);
//
//		BodyDetector detector;
//
//		EXPECT_TRUE(detector.DetectBody(image_body1));
//		EXPECT_TRUE(detector.DetectBody(image_body2));
//		EXPECT_TRUE(detector.DetectBody(image_body3));
//	}
	
	// DetectBody() On Image in Grayscale with Body.
//	TEST(BodyDetectorTest, ImageWithBodyInGrayscale)
//	{
//		Mat image_body_ir1 = imread("./img/body-ir1.jpg", IMREAD_GRAYSCALE);
//		Mat image_body1 = imread("./img/body1.jpg", IMREAD_GRAYSCALE);
//		Mat image_body2 = imread("./img/body2.jpg", IMREAD_GRAYSCALE);
//		Mat image_body3 = imread("./img/body3.jpg", IMREAD_GRAYSCALE);
//
//		assert(image_body_ir1.data != 0);
//		assert(image_body1.data != 0);
//		assert(image_body2.data != 0);
//		assert(image_body3.data != 0);
//
//		BodyDetector detector;
//
//		EXPECT_TRUE(detector.DetectBody(image_body_ir1));
//		EXPECT_TRUE(detector.DetectBody(image_body1));
//		EXPECT_TRUE(detector.DetectBody(image_body2));
//		EXPECT_TRUE(detector.DetectBody(image_body3));
//	}

	// DetectBody() On Image in Color without Body.
//	TEST(BodyDetectorTest, ImageWithoutBodyInColor)
//	{
//		Mat image_nobody1 = imread("./img/nobody1.jpg", IMREAD_COLOR);
//		Mat image_nobody2 = imread("./img/nobody2.jpg", IMREAD_COLOR);
//
//		assert(image_nobody1.data != 0);
//		assert(image_nobody2.data != 0);
//
//		BodyDetector detector;
//
//		EXPECT_FALSE(detector.DetectBody(image_nobody1));
//		EXPECT_FALSE(detector.DetectBody(image_nobody2));
//	}
	
	// DetectBody() On Image in Grayscale without Body.
//	TEST(BodyDetectorTest, ImageWithoutBodyInGrayscale)
//	{
//		Mat image_nobody1 = imread("./img/nobody1.jpg", IMREAD_GRAYSCALE);
//		Mat image_nobody2 = imread("./img/nobody2.jpg", IMREAD_GRAYSCALE);
//
//		assert(image_nobody1.data != 0);
//		assert(image_nobody2.data != 0);
//
//		BodyDetector detector;
//
//		EXPECT_FALSE(detector.DetectBody(image_nobody1));
//		EXPECT_FALSE(detector.DetectBody(image_nobody2));
//	}

} // namespace

#endif // MOTION_DETECTOR_TESTS_HPP
