#include "asv_state.hpp"

namespace hcv
{
	namespace asv
	{
		////////////// AlertState
		AlertState* AlertState::singleton = 0;

		IASVState* AlertState::Instance()
		{
			if (singleton == 0)
				singleton = new AlertState();
			return singleton;
		}

		IASVBaseState* AlertState::InstanceAsBase()
		{
			if (singleton == 0)
				singleton = new AlertState();
			return singleton;
		}

		////////////// IdleState
		IdleState* IdleState::singleton = 0;

		IASVState* IdleState::Instance()
		{
			if (singleton == 0)
				singleton = new IdleState();
			return singleton;
		}

		IASVBaseState* IdleState::InstanceAsBase()
		{
			if (singleton == 0)
				singleton = new IdleState();
			return singleton;
		}

		////////////// RecordingState
		RecordingState* RecordingState::singleton = 0;

		IASVState* RecordingState::Instance()
		{
			if (singleton == 0)
				singleton = new RecordingState();
			return singleton;
		}

		////////////// AlarmingState
		AlarmingState* AlarmingState::singleton = 0;

		IASVState* AlarmingState::Instance()
		{
			if (singleton == 0)
				singleton = new AlarmingState();
			return singleton;
		}

		////////////// RecordingAndAlarmingState
		RecordingAndAlarmingState* RecordingAndAlarmingState::singleton = 0;

		IASVState* RecordingAndAlarmingState::Instance()
		{
			if (singleton == 0)
				singleton = new RecordingAndAlarmingState();
			return singleton;
		}

	} // namespace asv
} // namespace hcv
