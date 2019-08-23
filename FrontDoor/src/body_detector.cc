#include "body_detector.hpp"

#include "macros.hpp"

#include <iostream>

using namespace std;

namespace hcv
{
	BodyDetector::BodyDetector()
	{
		PRINT("BodyDetector empty constructed.");
	}

	BodyDetector::BodyDetector(const BodyDetector& i_body_detector)
	{
		PRINT("BodyDetector copy constructed.");
	}

	BodyDetector::~BodyDetector()
	{
		PRINT("BodyDetector destroyed.");
	}

	//bool BodyDetector::DetectBody(const cv::Mat& i_img) {}

} // namespace hcv
