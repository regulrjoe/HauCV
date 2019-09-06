#include "srv/states.hpp"

#include "macros.hpp"
#include "retval.hpp"

#include <iostream>

namespace hcv
{
	namespace srv
	{
		/////////////////////////////
		AlertState* AlertState::singleton = 0;

		/////////////////////////////
		ISRVState* AlertState::Instance()
		{
			if (singleton == 0)
				singleton = new AlertState();
			return singleton;
		}

		/////////////////////////////
		ISRVBaseState* AlertState::InstanceAsBase()
		{
			if (singleton == 0)
				singleton = new AlertState();
			return singleton;
		}

		/////////////////////////////
		void AlertState::HandleMotion(SRVSystem* i_system)
		{
			try
			{
				i_system->GetTimer()->UpdateMotionTimestamps();

				startRecording(i_system);
				changeCurrentState(i_system, RecordingState::Instance());
				playAlertSound(i_system);
			}
			catch (const RetVal& rv)
			{
				cerr << "AlertState::HandleMotion(): An ERROR was caught with RetVal = " << RVMsg(rv) << "." << endl;
				throw(rv);
			}
			catch (const exception& e)
			{
				cerr << "AlertState::HandleMotion(): An EXCEPTION was caught with message = " << e.what() << "." << endl;
				throw(e);
			}
		}

	} // namespace srv
} // namespace hcv
