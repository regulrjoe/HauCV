#include "srv/states.hpp"

#include "macros.hpp"
#include "rcode.hpp"

namespace hcv
{
	namespace srv
	{

		/////////////////////////////
		RecordingState* RecordingState::singleton = 0;

		/////////////////////////////
		ISRVState* RecordingState::Instance()
		{
			if (singleton == 0)
				singleton = new RecordingState();
			return singleton;
		}

		/////////////////////////////
		void RecordingState::HandleMotion(SRVSystem* i_system)
		{
			try
			{
				i_system->GetTimer()->UpdateLastMotionTimestamp();

				if (i_system->GetTimer()->IsTimeToSoundAlarm())
				{
					soundAlarm(i_system);
					changeCurrentState(i_system, RecordingAndAlarmingState::Instance());
				}
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
		void RecordingState::HandleNoMotion(SRVSystem* i_system)
		{
			try
			{
				if (i_system->GetTimer()->IsTimeToStopRecording())
				{
					stopRecording(i_system);
					changeCurrentState(i_system, i_system->GetBaseState());
				}
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
