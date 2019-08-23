#ifndef BODY_DETECTOR_HPP
#define BODY_DETECTOR_HPP

#include <opencv2/opencv.hpp>

namespace hcv
{
	class BodyDetector
	{
		public:
			BodyDetector();

			BodyDetector(const BodyDetector&);

			~BodyDetector();

			//bool DetectBody(const cv::Mat&);
	};

} // namespace hcv

#endif // BODY_DETECTOR_HPP
