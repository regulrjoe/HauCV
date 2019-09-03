#ifndef MOTION_DETECTOR_HPP
#define MOTION_DETECTOR_HPP

#include <opencv2/opencv.hpp>

namespace hcv
{
	class MotionDetector
	{
		public:
			MotionDetector();

			MotionDetector(const cv::Mat&, const uint16_t& = 10000);

			MotionDetector(const MotionDetector&);

			~MotionDetector();

			bool DetectMotion(cv::Mat&);

			void SetReferenceFrame(const cv::Mat&);

			void SetMinimumArea(const uint16_t&);

		private:
			cv::Mat m_reference_frame;

			uint16_t m_min_area;
	};

} // namespace hcv

#endif // MOTION_DETECTOR_HPP
