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
		RetVal SRVSystem::Start(const uint16_t& i_runtime)
		{
			// Open Camera.
			cv::VideoCapture cap(0);
			if (!cap.isOpened())
				return RetVal::NOTOK;

			// Setup variables.
			cv::Mat frame;
			bool motion;
			time_point<system_clock> start, current;
			duration<double> elapsed_seconds;

			// Setup reference frame for motion detection.
			cap >> frame;
			m_p_motion_detector->SetReferenceFrame(frame);

			// If runtime is set, setup the timers for it.
			if (i_runtime > 0)
				start = system_clock::now();

			while (cap.isOpened())
			{
				// Time to stop?
				if (i_runtime > 0)
				{
					current = system_clock::now();
					elapsed_seconds = current - start;
					if (elapsed_seconds.count() >= i_runtime)
						break;
				}

				// No? Then get the frame man!
				cap >> frame;
				
				// Is someone moving in the frame?
				motion = m_p_motion_detector->DetectMotion(frame);
				if (motion)
				{
					// Yes.
					if (handleFrameWithMotion() != RetVal::OK)
					{
						cap.release();
						return RetVal::NOTOK;
					}
				}
				else
				{
					// No.
					if (handleFrameWithNoMotion() != RetVal::OK)
					{
						cap.release();
						return RetVal::NOTOK;
					}
				}
			}

			cap.release();

			return RetVal::OK;
		}

		///////////////////////////
		RetVal SRVSystem::Stop()
		{
			return RetVal::NOTOK;
		}

		///////////////////////////
		RetVal SRVSystem::changeCurrentState(ISRVState* i_p_state)
		{
			try
			{
				m_p_current_system_state = i_p_state;
				return RetVal::OK;
			}
			catch (const exception& e)
			{
				cout << "Exception caught at SRVSystem::changeCurrentState(): " << e.what() << endl;
				return RetVal::NOTOK;
			}
		}

		///////////////////////////
		RetVal SRVSystem::changeBaseState(ISRVBaseState* i_p_state)
		{
			try
			{
				m_p_base_system_state = i_p_state;
				return RetVal::OK;
			}
			catch (const exception& e)
			{
				cout << "Exception caught at SRVSystem::changeBaseState(): " << e.what() << endl;
				return RetVal::NOTOK;
			}
		}

		///////////////////////////
		RetVal SRVSystem::handleFrameWithMotion()
		{
			if (m_p_current_system_state->HandleMotion(this) != RetVal::OK)
			{
				cout << "An ERROR occurred at SRVSystem::handleFrameWithMotion(). Shutting down." << endl;
				return RetVal::NOTOK;
			}
			else
			{
				return RetVal::OK;
			}
		}

		///////////////////////////
		RetVal SRVSystem::handleFrameWithNoMotion()
		{
			if (m_p_current_system_state->HandleNoMotion(this) != RetVal::OK)
			{
				cout << "An ERROR occurred at SRVSystem::handleFrameWithNoMotion(). Shutting down." << endl;
				return RetVal::NOTOK;
			}
			else
			{
				return RetVal::OK;
			}
		}

	} // namespace srv
} // namespace hcv
