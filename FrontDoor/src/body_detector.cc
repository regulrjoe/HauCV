#include "body_detector.hpp"

#include <iostream>

using namespace std;

namespace hcv
{
	BodyDetector::BodyDetector()
	{
		cout << "BodyDetector empty constructed." << endl;
	}

	BodyDetector::BodyDetector(const BodyDetector& i_body_detector)
	{
		cout << "BodyDetector copy constructed." << endl;
	}

	BodyDetector::~BodyDetector()
	{
		cout << "BodyDetector destroyed." << endl;
	}

	//bool BodyDetector::DetectBody(const cv::Mat& i_img) {}

} // namespace hcv
