#include "motion_detector.hpp"

#include "macros.hpp"

#include <opencv2/imgproc.hpp>

#include <chrono>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

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
			const uint16_t& i_min_area) :
		m_min_area(i_min_area)
	{
		PRINT("MotionDetector constructed with parameters.");
		
		// Turn to grayscale.
		cv::cvtColor(i_reference_frame, m_reference_frame, cv::COLOR_BGR2GRAY);
		// Size down 50%.
		cv::resize(m_reference_frame, m_reference_frame, cv::Size(), 0.5, 0.5);
		// Apply Gaussian Blur.
		cv::GaussianBlur(m_reference_frame, m_reference_frame, cv::Size(21, 21), 0);
	}

	///////////////////////////////
	MotionDetector::MotionDetector(const MotionDetector& i_motion_detector) :
		m_reference_frame(i_motion_detector.m_reference_frame),
		m_min_area(i_motion_detector.m_min_area)
	{
		PRINT("MotionDetector copy constructed.");
	}

	///////////////////////////////
	MotionDetector::~MotionDetector()
	{
		PRINT("MotionDetector destroyed.");
	}

	///////////////////////////////
	bool MotionDetector::DetectMotion(cv::Mat& i_frame)
	{
		// TODO: Put this in a function at a higher level to modify all input images in system.
		//cv::resize(i_frame, inframe, 0, 0.5, 0.5);

		cv::Mat tmp = i_frame.clone();
		bool result = false;

		// Turn to grayscale.
		cv::cvtColor(tmp, tmp, cv::COLOR_BGR2GRAY);
		// Size down 50%.
		cv::resize(tmp, tmp, cv::Size(), 0.5, 0.5);
		// Apply Gaussian Blur.
		cv::GaussianBlur(tmp, tmp, cv::Size(21, 21), 0);
		// Compute absolute difference.
		cv::absdiff(tmp, m_reference_frame, tmp);
		// Apply threshold.
		cv::threshold(tmp, tmp, 25, 255, cv::THRESH_BINARY);
		// Dilate image to fill holes.
		cv::dilate(tmp, tmp, cv::Mat(), cv::Point(-1, -1), 2);

		// Find contours
		vector<vector<cv::Point> > contours;
		cv::findContours(tmp, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		cv::Rect contour_rect;
		// Iterate over the contours
		vector<vector<cv::Point> >::iterator it = contours.begin();
		for (it; it != contours.end(); ++it)
		{
			double contourArea = cv::contourArea(*it);

			// If contour is too small, ignore it.
			if (contourArea < m_min_area)
				continue;

			contour_rect = cv::boundingRect(*it);
			cv::rectangle(tmp, contour_rect, 125, 2);

			result = true;
		}
		
		// Save image to file.
		if (result)
			cv::imwrite("/app/tests/img/output/positive_" + to_string(system_clock::to_time_t(system_clock::now())) + ".jpg", tmp);
		else
			cv::imwrite("/app/tests/img/output/negative_" + to_string(system_clock::to_time_t(system_clock::now())) + ".jpg", tmp);

		return result;
	}

	///////////////////////////////
	void MotionDetector::SetReferenceFrame(const cv::Mat& i_reference_frame)
	{
		// Turn to grayscale.
		cv::cvtColor(i_reference_frame, m_reference_frame, cv::COLOR_BGR2GRAY);
		// Size down 50%.
		cv::resize(m_reference_frame, m_reference_frame, cv::Size(), 0.5, 0.5);
		// Apply Gaussian Blur.
		cv::GaussianBlur(m_reference_frame, m_reference_frame, cv::Size(21, 21), 0);

		PRINT("Reference frame updated.");
	}

	///////////////////////////////
	void MotionDetector::SetMinimumArea(const uint16_t& i_min_area)
	{
		m_min_area = i_min_area;
		PRINT("Minimum area updated.");
	}

} // namespace hcv
