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
		void IdleState::HandleMotion(SRVSystem* i_system)
		{
			try
			{
				i_system->GetTimer()->UpdateMotionTimestamps();

				startRecording(i_system);
				changeCurrentState(i_system, RecordingState::Instance());
			}
			catch (const RCode& rc)
			{
				printERROR(RCMsg(rc));
				throw rc;
			}
			catch (const exception& e)
			{
				printERROR(e.what());
				throw e;
			}
		}

	} // namespace srv
} // namespace hcv
