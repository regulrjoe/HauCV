#include "srv/system.hpp"

#include "macros.hpp"

#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std::chrono;
using namespace std;

namespace hcv
{
	namespace srv
	{
		///////////////////////////
		SRVSystem::SRVSystem(
				MotionDetector* const i_p_motion_detector,
				SRVTimer* const i_p_timer,
				ISRVBaseState* const i_p_base_state,
				Notifier* const i_p_notifier) :
			m_p_motion_detector(i_p_motion_detector),
			m_p_base_system_state(i_p_base_state),
			m_p_timer(i_p_timer),
			m_p_current_system_state(i_p_base_state),
			m_p_notifier(i_p_notifier)
		{
			PRINT("SRVSystem constructed.");
		}

		///////////////////////////
		SRVSystem::~SRVSystem()
		{
			delete m_p_motion_detector;
			delete m_p_base_system_state;
			delete m_p_current_system_state;
			delete m_p_timer;
			delete m_p_notifier;

			PRINT("SRVSystem destroyed.");
		}

		///////////////////////////
		RetVal SRVSystem::Start(const int& i_timer_in_secs)
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

	} // namespace srv
} // namespace hcv
