#include "srv/states.hpp"

#include "macros.hpp"
#include "rcode.hpp"

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
