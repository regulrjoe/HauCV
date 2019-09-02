#include "video_recorder.hpp"

#include "macros.hpp"

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
	bool VideoRecorder::IsRecording()
	{
		return m_recording;
	}

	////////////////////////////
	RetVal VideoRecorder::Start()
	{
		return RetVal::NOTOK;
	}

	////////////////////////////
	RetVal VideoRecorder::Stop()
	{
		return RetVal::NOTOK;
	}

	////////////////////////////
	RetVal VideoRecorder::Store()
	{
		return RetVal::NOTOK;
	}

} // namespace hcv
