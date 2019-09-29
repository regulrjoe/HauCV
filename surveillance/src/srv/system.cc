#include "srv/system.hpp"

#include "utils/macros.hpp"
#include "utils/rcode.hpp"

#include <dbg.h>

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
				AlarmFacade* const i_alarm_facade_ptr,
				Alert* const i_alert_ptr) :
			m_p_motion_detector(i_p_motion_detector),
			m_p_base_system_state(i_p_base_state),
			m_p_timer(i_p_timer),
			m_p_current_system_state(i_p_base_state),
			m_alarm_facade_ptr(i_alarm_facade_ptr),
			m_alert_ptr(i_alert_ptr)
		{
			dbg("SRVSystem::SRVSystem()");
			//printINFO("SRVSystem constructed.");
			m_context_ptr = new zmq::context_t(1);
			m_running_flag = false;
		}

		///////////////////////////
		SRVSystem::~SRVSystem()
		{
			dbg("SRVSystem::~SRVSystem()");
			delete m_alert_ptr;
			delete m_alarm_facade_ptr;
			delete m_p_motion_detector;
			delete m_p_base_system_state;
			delete m_p_current_system_state;
			delete m_p_timer;
		}

		///////////////////////////
		void SRVSystem::Start(const uint16_t& i_runtime)
		{
			dbg("SRVSystem::Start()");
			m_alarm_facade_ptr->Init(m_context_ptr);

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

				m_running_flag = true;

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
					cv::imshow("main", frame);
					
					// Is someone moving in the frame?
					if (m_p_motion_detector->DetectMotion(frame))
						handleFrameWithMotion();
					else
						handleFrameWithNoMotion();
				}

				cap.release();
				m_alarm_facade_ptr->Shutdown();
				m_running_flag = false;
			}
			catch (const RCode& rc)
			{
				printERROR(RCMsg(rc));
				cap.release();
			}
			catch (const exception& e)
			{
				printERROR(e.what());
				cap.release();
			}
		}

		///////////////////////////
		void SRVSystem::handleFrameWithMotion()
		{
			try
			{
				m_p_current_system_state->HandleFrameWithMotion(this);
			}
			catch (const RCode& rc)
			{
				printERROR(RCMsg(rc));
				throw rc;
			}
			catch (const exception& e)
			{
				printERROR(e.what());
				throw e;
			}
		}

		///////////////////////////
		void SRVSystem::handleFrameWithNoMotion()
		{
			try
			{
				m_p_current_system_state->HandleFrameWithNoMotion(this);
			}
			catch (const RCode& rc)
			{
				printERROR(RCMsg(rc));
				throw rc;
			}
			catch (const exception& e)
			{
				printERROR(e.what());
				throw e;
			}

		}

		///////////////////////////
		void SRVSystem::Stop()
		{
			dbg("SRVSystem::Stop()");
			m_running_flag = false;
		}

		///////////////////////////
		SRVTimer* SRVSystem::GetTimer()
		{
			return m_p_timer;
		}

		///////////////////////////
		AlarmFacade* SRVSystem::GetAlarm()
		{
			return m_alarm_facade_ptr;
		}

		Alert* SRVSystem::GetAlert()
		{
			dbg("SRVSystem::GetAlert()");
			return m_alert_ptr;
		}

		///////////////////////////
		ISRVBaseState* SRVSystem::GetBaseState()
		{
			dbg("SRVSystem::GetBaseState()");
			return m_p_base_system_state;
		}

		///////////////////////////
		void SRVSystem::changeCurrentState(ISRVState* i_p_state)
		{
			dbg("SRVSystem::changeCurrentState()");
			try
			{
				m_p_current_system_state = i_p_state;
			}
			catch (const RCode& rc)
			{
				printERROR(RCMsg(rc));
				throw rc;
			}
			catch (const exception& e)
			{
				printERROR(e.what());
				throw e;
			}
		}

		///////////////////////////
		void SRVSystem::changeBaseState(ISRVBaseState* i_p_state)
		{
			dbg("SRVSystem::changeBaseState()");
			try
			{
				m_p_base_system_state = i_p_state;
			}
			catch (const RCode& rc)
			{
				printERROR(RCMsg(rc));
				throw rc;
			}
			catch (const exception& e)
			{
				printERROR(e.what());
				throw e;
			}
		}
	} // namespace srv
} // namespace hcv
