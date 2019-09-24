#include "srv/states.hpp"

#include "macros.hpp"
#include "rcode.hpp"

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
		void AlarmingState::HandleMotion(SRVSystem* i_system)
		{
			try
			{
				i_system->GetTimer()->UpdateLastMotionTimestamp();
				startRecording(i_system);
				changeCurrentState(i_system, RecordingAndAlarmingState::Instance());
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

		/////////////////////////////
		void AlarmingState::HandleNoMotion(SRVSystem* i_system)
		{
			try
			{
				if (i_system->GetTimer()->IsTimeToStopAlarm())
					stopAlarm(i_system);
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

	} // namespace srv
} // namespace hcv
