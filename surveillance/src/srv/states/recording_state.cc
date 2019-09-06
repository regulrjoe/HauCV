#include "srv/states.hpp"

#include "macros.hpp"
#include "retval.hpp"

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
			catch (const RetVal& rv)
			{
				cerr << "RecordingState::HandleMotion(): An ERROR occurred: " << RVMsg(rv) << "." << endl;
				throw(rv);
			}
			catch (const exception& e)
			{
				cerr << "RecordingState::HandleMotion(): An EXCEPTION occurred with message = " << e.what() << "." << endl;
				throw(e);
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
			catch (const RetVal& rv)
			{
				cerr << "RecordingState::HandleNoMotion(): An ERROR occurred: " << RVMsg(rv) << "." << endl;
				throw(rv);
			}
			catch (const exception& e)
			{
				cerr << "RecordingState::HandleNoMotion(): An EXCEPTION occurred with message = " << e.what() << "." << endl;
				throw(e);
			}
		}

	} // namespace srv
} // namespace hcv
