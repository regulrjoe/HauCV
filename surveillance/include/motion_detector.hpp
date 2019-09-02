#ifndef MOTION_DETECTOR_HPP
#define MOTION_DETECTOR_HPP

#include <opencv2/opencv.hpp>

namespace hcv
{
	class MotionDetector
	{
		public:
			MotionDetector();

			MotionDetector(const cv::Mat&, const uint8_t& = uint8_t(500));

			MotionDetector(const MotionDetector&);

			~MotionDetector();

			bool DetectMotion(const cv::Mat&);

			void SetReferenceFrame(const cv::Mat&);

			void SetMinimumArea(const uint8_t&);

		private:
			cv::Mat m_reference_frame;

			uint8_t m_minimum_area;
	};

} // namespace hcv

#endif // MOTION_DETECTOR_HPP
