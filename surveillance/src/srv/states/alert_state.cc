#include "srv/states.hpp"

#include "utils/macros.hpp"
#include "utils/rcode.hpp"

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
		void AlertState::HandleFrameWithMotion(SRVSystem* i_system)
		{
			i_system->GetTimer()->UpdateMotionTimestamps();

			//startRecording(i_system);
			changeCurrentState(i_system, RecordingState::Instance());
			//playAlertSound(i_system);
		}

	} // namespace srv
} // namespace hcv
