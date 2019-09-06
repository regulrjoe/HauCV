#include "srv/states.hpp"

#include "macros.hpp"
#include "retval.hpp"

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
			catch (const RetVal& rv)
			{
				cerr << "IdleState::HandleMotion(): An ERROR was caught with RetVal = " << RVMsg(rv) << "." << endl;
				throw(rv);
			}
			catch (const exception& e)
			{
				cerr << "IdleState::HandleMotion(): An EXCEPTION was caught with message = " << e.what() << "." << endl;
				throw(e);
			}
		}

	} // namespace srv
} // namespace hcv
