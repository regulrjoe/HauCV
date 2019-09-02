#include "motion_detector.hpp"

#include "macros.hpp"

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
