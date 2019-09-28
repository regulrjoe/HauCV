#include "srv/states.hpp"

#include "utils/macros.hpp"
#include "utils/rcode.hpp"

#include <iostream>

namespace hcv
{
	namespace srv
	{
		/////////////////////////////
		AlarmingState* AlarmingState::singleton = 0;

		/////////////////////////////
		ISRVState* AlarmingState::Instance()
		{
			if (singleton == 0)
				singleton = new AlarmingState();
			return singleton;
		}

		/////////////////////////////
		void AlarmingState::HandleFrameWithMotion(SRVSystem* i_system)
		{
			i_system->GetTimer()->UpdateLastMotionTimestamp();
			//startRecording(i_system);
			changeCurrentState(i_system, RecordingAndAlarmingState::Instance());
		}

		/////////////////////////////
		void AlarmingState::HandleFrameWithNoMotion(SRVSystem* i_system)
		{
			if (i_system->GetTimer()->IsTimeToStopAlarm())
				i_system->GetAlarm()->Stop();
		}

	} // namespace srv
} // namespace hcv
