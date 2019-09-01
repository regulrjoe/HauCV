#ifndef VIDEO_RECORDER_HPP
#define VIDEO_RECORDER_HPP

#include "retval.hpp"

namespace hcv
{
	class VideoRecorder
	{
		public:
			VideoRecorder();

			~VideoRecorder();

			bool IsRecording();

			RetVal Start();

			RetVal Stop();

			RetVal Store();

		private:
			bool m_recording;
	};

} // namespace hcv

#endif // VIDEO_RECORDER_HPP
