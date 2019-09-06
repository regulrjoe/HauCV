#include "video_recorder.hpp"

#include "macros.hpp"
#include "retval.hpp"

#include <iostream>

using namespace std;

namespace hcv
{
	
	////////////////////////////
	VideoRecorder::VideoRecorder() : m_recording(false)
	{
		PRINT("VideoRecorder empty constructed.");
	}

	////////////////////////////
	VideoRecorder::~VideoRecorder()
	{
		PRINT("VideoRecorder destroyed.");
	}

	////////////////////////////
	void VideoRecorder::Do()
	{
		// TODO.
	}

	////////////////////////////
	bool VideoRecorder::IsRecording()
	{
		return m_recording;
	}

	////////////////////////////
	void VideoRecorder::Start()
	{
		// TODO.
		if (!m_recording)
		{
			m_recording = true;
		}
		else
		{
			cerr << "VideoRecorder is already recording." << endl;
		}
	}

	////////////////////////////
	void VideoRecorder::Stop()
	{
		// TODO.
		if (m_recording)
		{
			m_recording = false;
		}
		else
		{
			cerr << "VideoRecorder is already stopped" << endl;
		}
	}

} // namespace hcv
