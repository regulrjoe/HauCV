#include "srv/states.hpp"

#include "utils/macros.hpp"
#include "utils/rcode.hpp"

namespace hcv
{
	namespace srv
	{
		/////////////////////////////
		IdleState* IdleState::singleton = 0;

		/////////////////////////////
		ISRVState* IdleState::Instance()
		{
			if (singleton == 0)
				singleton = new IdleState();
			return singleton;
		}

		/////////////////////////////
		ISRVBaseState* IdleState::InstanceAsBase()
		{
			if (singleton == 0)
				singleton = new IdleState();
			return singleton;
		}

		/////////////////////////////
		void IdleState::HandleFrameWithMotion(SRVSystem* i_system)
		{
			i_system->GetTimer()->UpdateMotionTimestamps();

			//startRecording(i_system);
			changeCurrentState(i_system, RecordingState::Instance());
		}

	} // namespace srv
} // namespace hcv
