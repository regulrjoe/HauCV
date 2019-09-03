#include "motion_detector.hpp"

#include "macros.hpp"

#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;

namespace hcv
{
	///////////////////////////////
	MotionDetector::MotionDetector()
	{
		PRINT("MotionDetector empty constructed.");
	}

	///////////////////////////////
	MotionDetector::MotionDetector(
			const cv::Mat& i_reference_frame, 
			const uint8_t& i_minimum_area) :
		m_reference_frame(i_reference_frame),
		m_minimum_area(i_minimum_area)
	{
		PRINT("MotionDetector constructed with parameters.");
	}

	///////////////////////////////
	MotionDetector::MotionDetector(const MotionDetector& i_motion_detector) :
		m_reference_frame(i_motion_detector.m_reference_frame),
		m_minimum_area(i_motion_detector.m_minimum_area)
	{
		PRINT("MotionDetector copy constructed.");
	}

	///////////////////////////////
	MotionDetector::~MotionDetector()
	{
		PRINT("MotionDetector destroyed.");
	}

	///////////////////////////////
	bool MotionDetector::DetectMotion(const cv::Mat& i_frame)
	{
		// TODO: Put this in a function at a higher level to modify all input images in system.
		//cv::Mat inframe;

		//cv::resize(i_frame, inframe, 0, 0.5, 0.5);
		//cv::cvtColor(inframe, inframe, COLOR_BGR2GRAY);
		//cv::GaussianBlur(inframe, inframe, cv::Size(21, 21), 0);

		// Compute absolute difference.
		cv::Mat delta_frame;
		cv::absdiff(i_frame, m_reference_frame, delta_frame);

		// Apply threshold.
		cv::Mat thresh_frame;
		cv::threshold(delta_frame, thresh_frame, 25, 255, THRESH_BINARY);

		// Dilate image to fill holes.
		cv::Mat dilate_frame;
		cv::dilate(thresh_frame, dilate_frame, cv::Mat(), cv::Point(-1, -1), 2);

		// Find contours
		cv::Mat contours_frame;
		//TODO
		cv::findContours();


		return false;
	}

	///////////////////////////////
	void MotionDetector::SetReferenceFrame(const cv::Mat& i_reference_frame)
	{
		m_reference_frame = i_reference_frame;
		PRINT("Reference frame updated.");
	}

	///////////////////////////////
	void MotionDetector::SetMinimumArea(const uint8_t& i_minimum_area)
	{
		m_minimum_area = i_minimum_area;
		PRINT("Minimum area updated.");
	}

} // namespace hcv
