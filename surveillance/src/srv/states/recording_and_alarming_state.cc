#include "srv/states.hpp"

#include "utils/macros.hpp"
#include "utils/rcode.hpp"

namespace hcv
{
	namespace srv
	{

		/////////////////////////////
		RecordingAndAlarmingState* RecordingAndAlarmingState::singleton = 0;

		/////////////////////////////
		ISRVState* RecordingAndAlarmingState::Instance()
		{
			if (singleton == 0)
				singleton = new RecordingAndAlarmingState();
			return singleton;
		}

		/////////////////////////////
		void RecordingAndAlarmingState::HandleFrameWithMotion(SRVSystem* i_system)
		{
			i_system->GetTimer()->UpdateLastMotionTimestamp();
		}

		/////////////////////////////
		void RecordingAndAlarmingState::HandleFrameWithNoMotion(SRVSystem* i_system)
		{
			if (i_system->GetTimer()->IsTimeToStopRecording() && i_system->GetTimer()->IsTimeToStopAlarm())
			{
				//stopRecording(i_system);
				i_system->GetAlarm()->Stop();
				this->changeCurrentState(i_system, i_system->GetBaseState());
			}
			else if (i_system->GetTimer()->IsTimeToStopRecording())
			{
				//stopRecording(i_system);
				this->changeCurrentState(i_system, AlarmingState::Instance());
			}
			else if (i_system->GetTimer()->IsTimeToStopAlarm())
			{
				i_system->GetAlarm()->Stop();
				this->changeCurrentState(i_system, RecordingState::Instance());
			}
		}
	} // namespace srv
} // namespace hcv
