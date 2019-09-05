#include "srv/state.hpp"

namespace hcv
{
	namespace srv
	{
		////////////// ISRVState

		///////
		RetVal ISRVState::changeBaseState(SRVSystem* i_system, ISRVBaseState* i_base_state)
		{
			return i_system->changeBaseState(i_base_state);
		}

		///////
		RetVal ISRVState::changeCurrentState(SRVSystem* i_system, ISRVState* i_state)
		{
			return i_system->changeCurrentState(i_state);
		}

		////////////// ISRVBaseState

		///////
		ISRVBaseState::~ISRVBaseState() {}

		///////
		RetVal ISRVBaseState::startRecording(SRVSystem* i_system)
		{
			//TODO.
			return RetVal::NOTOK;
		}


		////////////// AlertState
		AlertState* AlertState::singleton = 0;

		///////
		ISRVState* AlertState::Instance()
		{
			if (singleton == 0)
				singleton = new AlertState();
			return singleton;
		}

		///////
		ISRVBaseState* AlertState::InstanceAsBase()
		{
			if (singleton == 0)
				singleton = new AlertState();
			return singleton;
		}

		///////
		RetVal AlertState::HandleMotion(SRVSystem* i_system)
		{
			this->startRecording(i_system);
			this->changeCurrentState(i_system, RecordingState::Instance());
			this->playAlertSound();
			return RetVal::OK;
		}

		///////
		RetVal AlertState::playAlertSound()
		{
			// TODO.
			return RetVal::NOTOK;
		}

		///////
		RetVal AlertState::HandleNoMotion(SRVSystem* i_system)
		{
			// TODO.
			return RetVal::NOTOK;
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

		///////
		RetVal IdleState::HandleMotion(SRVSystem* i_system)
		{
			// TODO.
			return RetVal::NOTOK;
		}

		///////
		RetVal IdleState::HandleNoMotion(SRVSystem* i_system)
		{
			// TODO.
			return RetVal::NOTOK;
		}
		
		////////////// RecordingState
		RecordingState* RecordingState::singleton = 0;

		ISRVState* RecordingState::Instance()
		{
			if (singleton == 0)
				singleton = new RecordingState();
			return singleton;
		}

		///////
		RetVal RecordingState::HandleMotion(SRVSystem* i_system)
		{
			// TODO.
			return RetVal::NOTOK;
		}

		///////
		RetVal RecordingState::HandleNoMotion(SRVSystem* i_system)
		{
			// TODO.
			return RetVal::NOTOK;
		}

		///////
		RetVal RecordingState::soundAlarm()
		{
			// TODO.
			return RetVal::NOTOK;
		}

		///////
		RetVal RecordingState::stopRecording()
		{
			// TODO.
			return RetVal::NOTOK;
		}

		///////
		RetVal RecordingState::storeVideo()
		{
			// TODO.
			return RetVal::NOTOK;
		}

		////////////// AlarmingState
		AlarmingState* AlarmingState::singleton = 0;

		ISRVState* AlarmingState::Instance()
		{
			if (singleton == 0)
				singleton = new AlarmingState();
			return singleton;
		}

		///////
		RetVal AlarmingState::HandleMotion(SRVSystem* i_system)
		{
			// TODO.
			return RetVal::NOTOK;
		}

		///////
		RetVal AlarmingState::HandleNoMotion(SRVSystem* i_system)
		{
			// TODO.
			return RetVal::NOTOK;
		}

		///////
		RetVal AlarmingState::startRecording()
		{
			// TODO.
			return RetVal::NOTOK;
		}

		///////
		RetVal AlarmingState::stopAlarm()
		{
			// TODO.
			return RetVal::NOTOK;
		}

		////////////// RecordingAndAlarmingState
		RecordingAndAlarmingState* RecordingAndAlarmingState::singleton = 0;

		ISRVState* RecordingAndAlarmingState::Instance()
		{
			if (singleton == 0)
				singleton = new RecordingAndAlarmingState();
			return singleton;
		}

		///////
		RetVal RecordingAndAlarmingState::HandleMotion(SRVSystem* i_system)
		{
			// TODO.
			return RetVal::NOTOK;
		}

		///////
		RetVal RecordingAndAlarmingState::HandleNoMotion(SRVSystem* i_system)
		{
			// TODO.
			return RetVal::NOTOK;
		}

		///////
		RetVal RecordingAndAlarmingState::stopAlarm()
		{
			// TODO.
			return RetVal::NOTOK;
		}

	} // namespace srv
} // namespace hcv
