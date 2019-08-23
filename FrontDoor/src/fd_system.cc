#include "fd_system.hpp"

#include "macros.hpp"

#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std::chrono;
using namespace std;
using namespace hcv;

///////////////////////////
FDSystem::FDSystem(
		BodyDetector* const i_p_body_detector, 
		IFDBaseState* const i_p_base_state, 
		FDTimers* const i_p_timers) : 
	m_p_body_detector(i_p_body_detector), 
	m_p_base_system_state(i_p_base_state), 
	m_p_current_system_state(i_p_base_state), 
	m_p_timers(i_p_timers)
{
	PRINT("FDSystem constructed.");
}

///////////////////////////
FDSystem::~FDSystem()
{
	delete m_p_body_detector;
	delete m_p_base_system_state;
	delete m_p_current_system_state;
	delete m_p_timers;

	PRINT("FDSystem destroyed.");
}

///////////////////////////
bool FDSystem::Start(const int& i_timer_in_secs)
{
	// Open Camera.
	cv::VideoCapture cap(0);
	if (!cap.isOpened())
		return false;

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

	return true;
}
