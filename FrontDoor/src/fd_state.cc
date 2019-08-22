#include "fd_state.hpp"

namespace hcv
{
	////////////// AlertState
	AlertState* AlertState::singleton = 0;

	IFDState* AlertState::Instance()
	{
		if (singleton == 0)
			singleton = new AlertState();
		return singleton;
	}

	IFDBaseState* AlertState::InstanceAsBase()
	{
		if (singleton == 0)
			singleton = new AlertState();
		return singleton;
	}

	////////////// IdleState
	IdleState* IdleState::singleton = 0;

	IFDState* IdleState::Instance()
	{
		if (singleton == 0)
			singleton = new IdleState();
		return singleton;
	}

	IFDBaseState* IdleState::InstanceAsBase()
	{
		if (singleton == 0)
			singleton = new IdleState();
		return singleton;
	}

	////////////// RecordingState
	RecordingState* RecordingState::singleton = 0;

	IFDState* RecordingState::Instance()
	{
		if (singleton == 0)
			singleton = new RecordingState();
		return singleton;
	}

	////////////// AlarmingState
	AlarmingState* AlarmingState::singleton = 0;

	IFDState* AlarmingState::Instance()
	{
		if (singleton == 0)
			singleton = new AlarmingState();
		return singleton;
	}

	////////////// RecordingAndAlarmingState
	RecordingAndAlarmingState* RecordingAndAlarmingState::singleton = 0;

	IFDState* RecordingAndAlarmingState::Instance()
	{
		if (singleton == 0)
			singleton = new RecordingAndAlarmingState();
		return singleton;
	}

} // namespace hcv
