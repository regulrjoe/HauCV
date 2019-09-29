#include "srv/states.hpp"

#include <dbg.h>

namespace hcv
{
	namespace srv
	{
		
		/////////////////////////////////
		/////////// ISRVState ///////////
		/////////////////////////////////

		///////////////////////
		ISRVState::~ISRVState() {}

		///////////////////////
		void ISRVState::changeBaseState(SRVSystem* i_system, ISRVBaseState* i_base_state)
		{
			i_system->changeBaseState(i_base_state);
		}

		///////////////////////
		void ISRVState::changeCurrentState(SRVSystem* i_system, ISRVState* i_state)
		{
			i_system->changeCurrentState(i_state);
		}


		/////////////////////////////////
		///////// ISRVBaseState /////////
		/////////////////////////////////

		///////////////////////
		ISRVBaseState::~ISRVBaseState() {}


		/////////////////////////////////
		/////////// AlertState //////////
		/////////////////////////////////

		///////////////////////
		AlertState* AlertState::singleton = 0;

		///////////////////////
		ISRVState* AlertState::Instance()
		{
			if (singleton == 0)
				singleton = new AlertState();
			return singleton;
		}

		///////////////////////
		ISRVBaseState* AlertState::InstanceAsBase()
		{
			if (singleton == 0)
				singleton = new AlertState();
			return singleton;
		}

		///////////////////////
		void AlertState::HandleFrameWithMotion(SRVSystem* i_system)
		{
			dbg("AlertState::HandleFrameWithMotion");
			i_system->GetTimer()->UpdateMotionTimestamps();

			//startRecording(i_system);
			i_system->GetAlert()->Play();

			changeCurrentState(i_system, RecordingState::Instance());
		}

		///////////////////////
		void AlertState::HandleFrameWithNoMotion(SRVSystem* i_system)
		{
			// Do Nothing.
		}


		/////////////////////////////////
		/////////// IdleState ///////////
		/////////////////////////////////

		///////////////////////
		IdleState* IdleState::singleton = 0;

		///////////////////////
		ISRVState* IdleState::Instance()
		{
			if (singleton == 0)
				singleton = new IdleState();
			return singleton;
		}

		///////////////////////
		ISRVBaseState* IdleState::InstanceAsBase()
		{
			if (singleton == 0)
				singleton = new IdleState();
			return singleton;
		}

		///////////////////////
		void IdleState::HandleFrameWithMotion(SRVSystem* i_system)
		{
			i_system->GetTimer()->UpdateMotionTimestamps();

			//startRecording(i_system);
			changeCurrentState(i_system, RecordingState::Instance());
		}

		///////////////////////
		void IdleState::HandleFrameWithNoMotion(SRVSystem* i_system)
		{
			// Do Nothing.
		}
		

		/////////////////////////////////
		//////// RecordingState /////////
		/////////////////////////////////

		///////////////////////
		RecordingState* RecordingState::singleton = 0;

		///////////////////////
		ISRVState* RecordingState::Instance()
		{
			if (singleton == 0)
				singleton = new RecordingState();
			return singleton;
		}

		///////////////////////
		void RecordingState::HandleFrameWithMotion(SRVSystem* i_system)
		{
			i_system->GetTimer()->UpdateLastMotionTimestamp();

			if (i_system->GetTimer()->IsTimeToSoundAlarm())
			{
				if (i_system->GetBaseState() == AlertState::InstanceAsBase())
					i_system->GetAlarm()->Start();

				this->changeCurrentState(i_system, RecordingAndAlarmingState::Instance());
			}
		}

		///////////////////////
		void RecordingState::HandleFrameWithNoMotion(SRVSystem* i_system)
		{
			if (i_system->GetTimer()->IsTimeToStopRecording())
			{
				//stopRecording(i_system);
				this->changeCurrentState(i_system, i_system->GetBaseState());
			}
		}


		/////////////////////////////////
		///////// AlarmingState /////////
		/////////////////////////////////

		///////////////////////
		AlarmingState* AlarmingState::singleton = 0;

		///////////////////////
		ISRVState* AlarmingState::Instance()
		{
			if (singleton == 0)
				singleton = new AlarmingState();
			return singleton;
		}

		///////////////////////
		void AlarmingState::HandleFrameWithMotion(SRVSystem* i_system)
		{
			i_system->GetTimer()->UpdateLastMotionTimestamp();
			//startRecording(i_system);
			changeCurrentState(i_system, RecordingAndAlarmingState::Instance());
		}

		///////////////////////
		void AlarmingState::HandleFrameWithNoMotion(SRVSystem* i_system)
		{
			if (i_system->GetTimer()->IsTimeToStopAlarm())
				i_system->GetAlarm()->Stop();
		}

		
		/////////////////////////////////
		/// RecordingAndAlarmingState ///
		/////////////////////////////////

		///////////////////////
		RecordingAndAlarmingState* RecordingAndAlarmingState::singleton = 0;

		///////////////////////
		ISRVState* RecordingAndAlarmingState::Instance()
		{
			if (singleton == 0)
				singleton = new RecordingAndAlarmingState();
			return singleton;
		}

		///////////////////////
		void RecordingAndAlarmingState::HandleFrameWithMotion(SRVSystem* i_system)
		{
			i_system->GetTimer()->UpdateLastMotionTimestamp();
		}

		///////////////////////
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
