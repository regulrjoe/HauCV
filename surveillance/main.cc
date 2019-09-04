#include "motion_detector.hpp"

#include <opencv2/opencv.hpp>

#include <assert.h>
#include <iostream>

using namespace std;
using namespace cv;
using namespace hcv;

int main()
{
	Mat base_image = imread("/app/tests/img/B_base.jpg", IMREAD_GRAYSCALE);
	Mat test_body = imread("/app/tests/img/B_body1.jpg", IMREAD_GRAYSCALE);

	assert(base_image.data != 0);
	assert(test_body.data != 0);

	MotionDetector detector(base_image, uint8_t(400));

	cout << detector.DetectMotion(test_body) << endl;

	return 0;
}
