#include "srv/state.hpp"

namespace hcv
{
	namespace srv
	{
		////////////// AlertState
		AlertState* AlertState::singleton = 0;

		ISRVState* AlertState::Instance()
		{
			if (singleton == 0)
				singleton = new AlertState();
			return singleton;
		}

		ISRVBaseState* AlertState::InstanceAsBase()
		{
			if (singleton == 0)
				singleton = new AlertState();
			return singleton;
		}

		////////////// IdleState
		IdleState* IdleState::singleton = 0;

		ISRVState* IdleState::Instance()
		{
			if (singleton == 0)
				singleton = new IdleState();
			return singleton;
		}

		ISRVBaseState* IdleState::InstanceAsBase()
		{
			if (singleton == 0)
				singleton = new IdleState();
			return singleton;
		}

		////////////// RecordingState
		RecordingState* RecordingState::singleton = 0;

		ISRVState* RecordingState::Instance()
		{
			if (singleton == 0)
				singleton = new RecordingState();
			return singleton;
		}

		////////////// AlarmingState
		AlarmingState* AlarmingState::singleton = 0;

		ISRVState* AlarmingState::Instance()
		{
			if (singleton == 0)
				singleton = new AlarmingState();
			return singleton;
		}

		////////////// RecordingAndAlarmingState
		RecordingAndAlarmingState* RecordingAndAlarmingState::singleton = 0;

		ISRVState* RecordingAndAlarmingState::Instance()
		{
			if (singleton == 0)
				singleton = new RecordingAndAlarmingState();
			return singleton;
		}

	} // namespace srv
} // namespace hcv
