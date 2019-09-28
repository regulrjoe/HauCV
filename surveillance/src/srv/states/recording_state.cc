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
		void RecordingState::HandleFrameWithMotion(SRVSystem* i_system)
		{
			i_system->GetTimer()->UpdateLastMotionTimestamp();

			if (i_system->GetTimer()->IsTimeToSoundAlarm())
			{
				i_system->GetAlarm()->Start();
				this->changeCurrentState(i_system, RecordingAndAlarmingState::Instance());
			}
		}

		/////////////////////////////
		void RecordingState::HandleFrameWithNoMotion(SRVSystem* i_system)
		{
			if (i_system->GetTimer()->IsTimeToStopRecording())
			{
				//stopRecording(i_system);
				this->changeCurrentState(i_system, i_system->GetBaseState());
			}
		}

	} // namespace srv
} // namespace hcv
