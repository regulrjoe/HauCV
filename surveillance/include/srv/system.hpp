#ifndef SRV_SYSTEM_HPP
#define SRV_SYSTEM_HPP

#include "srv/states.hpp"
#include "srv/timer.hpp"

#include "motion_detector.hpp"
#include "notifier.hpp"

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

				void Start(const uint16_t&);

				void Stop();

				SRVTimer* GetTimer();

				ISRVBaseState* GetBaseState();

			private:
				friend class ISRVState;

				//// State-specific behaviour
				void handleFrameWithMotion();
	
				void handleFrameWithNoMotion();

				//// State-independent behaviour
				void changeBaseState(ISRVBaseState*);
	
				void changeCurrentState(ISRVState*);

				void playAlertSound();

				void soundAlarm();

				void startRecording();

				void stopAlarm();

				void stopRecording();


			//// Data
			private:
				MotionDetector* m_p_motion_detector;

				SRVTimer* m_p_timer;

				ISRVBaseState* m_p_base_system_state;

				ISRVState* m_p_current_system_state;

				Notifier* m_p_notifier;

				bool m_is_started;

		};

	} // namespace srv
} // namespace hcv

#endif // SRV_SYSTEM_HPP
