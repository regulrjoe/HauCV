#ifndef SOUND_CONTROLLER_HPP
#define SOUND_CONTROLLER_HPP

namespace hcv
{
	class SoundController
	{
		public:
			SoundController();

			SoundController(const SoundController&);

			~SoundController();

			bool IsAlarmOn();

			void SoundAlarm();

			void SoundAlert();

			void StopAlarm();

		private:
			bool m_alarm_is_on;
	};

} // namespace hcv

#endif // SOUND_CONTROLLER_HPP
