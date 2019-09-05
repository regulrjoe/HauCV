#ifndef SRV_SYSTEM_HPP
#define SRV_SYSTEM_HPP

#include "srv/state.hpp"
#include "srv/timer.hpp"

#include "motion_detector.hpp"
#include "notifier.hpp"
#include "retval.hpp"

#include <cstdint>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

namespace hcv
{
	namespace srv
	{
		class ISRVState;
		class ISRVBaseState;

		class SRVSystem
		{
			//// Methods
			public:
				SRVSystem(MotionDetector* const, SRVTimer* const, ISRVBaseState* const, Notifier* const);

				~SRVSystem();

				RetVal Start(const uint16_t&);

				RetVal Stop();

			private:
				friend class ISRVState;

				RetVal changeBaseState(ISRVBaseState*);
	
				RetVal changeCurrentState(ISRVState*);
	
				RetVal handleFrameWithMotion();
	
				RetVal handleFrameWithNoMotion();

			//// Data
			private:
				MotionDetector* m_p_motion_detector;

				SRVTimer* m_p_timer;

				ISRVBaseState* m_p_base_system_state;

				ISRVState* m_p_current_system_state;

				Notifier* m_p_notifier;

		};

	} // namespace srv
} // namespace hcv

#endif // SRV_SYSTEM_HPP
