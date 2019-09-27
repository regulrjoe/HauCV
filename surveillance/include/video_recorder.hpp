#ifndef VIDEO_RECORDER_HPP
#define VIDEO_RECORDER_HPP

namespace hcv
{
	class VideoRecorder
	{
		public:
			VideoRecorder();

			~VideoRecorder();

			void Do();

			bool IsRecording();

			void Start();

			void Stop();

		private:
			bool m_recording;
	};

} // namespace hcv

#endif // VIDEO_RECORDER_HPP
