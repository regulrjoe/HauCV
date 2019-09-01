#include "asv_system.hpp"

#include "macros.hpp"

#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std::chrono;
using namespace std;

namespace hcv
{
	namespace asv
	{
		///////////////////////////
		ASVSystem::ASVSystem(
				BodyDetector* const i_p_body_detector,
				ASVTimer* const i_p_timer,
				IASVBaseState* const i_p_base_state,
				Notifier* const i_p_notifier) :
			m_p_body_detector(i_p_body_detector),
			m_p_base_system_state(i_p_base_state),
			m_p_timer(i_p_timer),
			m_p_current_system_state(i_p_base_state),
			m_p_notifier(i_p_notifier)
		{
			PRINT("ASVSystem constructed.");
		}

		///////////////////////////
		ASVSystem::~ASVSystem()
		{
			delete m_p_body_detector;
			delete m_p_base_system_state;
			delete m_p_current_system_state;
			delete m_p_timer;
			delete m_p_notifier;

			PRINT("ASVSystem destroyed.");
		}

		///////////////////////////
		RetVal ASVSystem::Start(const int& i_timer_in_secs)
		{
			// Open Camera.
			cv::VideoCapture cap(0);
			if (!cap.isOpened())
				return RetVal::NOTOK;

			// Setup timer.
			time_point<system_clock> start, current;
			duration<double> elapsed_seconds;
			start = system_clock::now();

			cv::Mat frame;
			while (cap.isOpened())
			{
				cap >> frame;

				current = system_clock::now();
				elapsed_seconds = current - start;
				if (elapsed_seconds.count() >= i_timer_in_secs)
					break;
			}
			cap.release();

			return RetVal::OK;
		}

	} // namespace asv
} // namespace hcv
