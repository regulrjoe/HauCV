#ifndef SOUND_CONTROLLER_HPP
#define SOUND_CONTROLLER_HPP

#include "retval.hpp"

namespace hcv
{
	class SoundController
	{
		public:
			SoundController();

			SoundController(const SoundController&);

			~SoundController();

			bool IsAlarmOn();

			RetVal SoundAlarm();

			RetVal SoundAlert();

			RetVal StopAlarm();

		private:
			bool m_alarm_is_on;
	};

} // namespace hcv

#endif // SOUND_CONTROLLER_HPP
