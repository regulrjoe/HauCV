#include "srv/states.hpp"

#include "macros.hpp"
#include "rcode.hpp"

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
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				throw rc;
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				throw e;
			}
		}

	} // namespace srv
} // namespace hcv
