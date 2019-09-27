#include "srv/states.hpp"

#include "utils/macros.hpp"
#include "utils/rcode.hpp"

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
					startAlarm(i_system);
					changeCurrentState(i_system, RecordingAndAlarmingState::Instance());
				}
			}
			catch (const RCode& rc)
			{
				printERROR(RCMsg(rc));
				throw rc;
			}
			catch (const exception& e)
			{
				printERROR(e.what());
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
				printERROR(RCMsg(rc));
				throw rc;
			}
			catch (const exception& e)
			{
				printERROR(e.what());
				throw e;
			}
		}

	} // namespace srv
} // namespace hcv
