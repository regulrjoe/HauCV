#include "srv/system.hpp"

#include "macros.hpp"
#include "rcode.hpp"

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
		void SRVSystem::Start(const uint16_t& i_runtime)
		{
			// Setup variables.
			bool motion;
			cv::Mat frame;
			duration<double> elapsed_seconds;
			time_point<system_clock> start, current;

			// Open Camera.
			cv::VideoCapture cap(0);

			try
			{
				if (!cap.isOpened())
					throw RCode::NOTOK; // TODO: Set proper RCode.

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
					if (m_p_motion_detector->DetectMotion(frame))
						handleFrameWithMotion();
					else
						handleFrameWithNoMotion();
				}

				cap.release();
			}
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				cap.release();
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				cap.release();
			}
		}

		///////////////////////////
		void SRVSystem::handleFrameWithMotion()
		{
			try
			{
				m_p_current_system_state->HandleMotion(this);
			}
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				throw rc;
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				throw e;
			}
		}

		///////////////////////////
		void SRVSystem::handleFrameWithNoMotion()
		{
			try
			{
				m_p_current_system_state->HandleNoMotion(this);
			}
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				throw rc;
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				throw e;
			}

		}

		///////////////////////////
		void SRVSystem::Stop()
		{
			// TODO.
		}

		///////////////////////////
		SRVTimer* SRVSystem::GetTimer()
		{
			return m_p_timer;
		}

		ISRVBaseState* SRVSystem::GetBaseState()
		{
			return m_p_base_system_state;
		}

		///////////////////////////
		void SRVSystem::changeCurrentState(ISRVState* i_p_state)
		{
			try
			{
				m_p_current_system_state = i_p_state;
			}
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				throw rc;
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				throw e;
			}
		}

		///////////////////////////
		void SRVSystem::changeBaseState(ISRVBaseState* i_p_state)
		{
			try
			{
				m_p_base_system_state = i_p_state;
			}
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				throw rc;
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				throw e;
			}
		}

		///////////////////////////
		void SRVSystem::playAlertSound()
		{
			// TODO.
		}

		///////////////////////////
		void SRVSystem::soundAlarm()
		{
			// TODO.
		}

		///////////////////////////
		void SRVSystem::startRecording()
		{
			// TODO.
		}

		///////////////////////////
		void SRVSystem::stopAlarm()
		{
			// TODO.
		}

		///////////////////////////
		void SRVSystem::stopRecording()
		{
			// TODO.
		}

	} // namespace srv
} // namespace hcv
