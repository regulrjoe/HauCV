#include "srv/states.hpp"

#include "utils/macros.hpp"
#include "utils/rcode.hpp"

#include <dbg.h>

namespace hcv
{
	namespace srv
	{

		/////////////////////////////
		ISRVState::~ISRVState() {}

		/////////////////////////////
		void ISRVState::HandleFrameWithMotion(SRVSystem* i_system)
		{
			// Do nothing.
		}

		/////////////////////////////
		void ISRVState::HandleFrameWithNoMotion(SRVSystem* i_system)
		{
			// Do nothing.
		}

		/////////////////////////////
		void ISRVState::changeBaseState(SRVSystem* i_system, ISRVBaseState* i_base_state)
		{
			i_system->changeBaseState(i_base_state);
		}

		/////////////////////////////
		void ISRVState::changeCurrentState(SRVSystem* i_system, ISRVState* i_state)
		{
			i_system->changeCurrentState(i_state);
		}
	} // namespace srv
} // namespace hcv
