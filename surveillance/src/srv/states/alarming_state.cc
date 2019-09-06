#include "srv/states.hpp"

#include "macros.hpp"
#include "retval.hpp"

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
			catch (const RetVal& rv)
			{
				cerr << "AlarmingState::HandleMotion(): An ERROR was caught with RetVal = " << RVMsg(rv) << "." << endl;
				throw(rv);
			}
			catch (const exception& e)
			{
				cerr << "AlarmingState::HandleMotion(): An EXCEPTION was caught with message = " << e.what() << "." << endl;
				throw(e);
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
			catch (const RetVal& rv)
			{
				cerr << "AlarmingState::HandleNoMotion(): An ERROR was caught with RetVal = " << RVMsg(rv) << "." << endl;
				throw(rv);
			}
			catch (const exception& e)
			{
				cerr << "AlarmingState::HandleNoMotion(): An EXCEPTION was caught with message = " << e.what() << "." << endl;
				throw(e);
			}
		}

	} // namespace srv
} // namespace hcv
