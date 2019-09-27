#ifndef SRV_SYSTEM_HPP
#define SRV_SYSTEM_HPP

#include "srv/states.hpp"
#include "srv/timer.hpp"

#include "alarm/alarm_facade.hpp"

#include "motion_detector.hpp"

#include <zmq.hpp>

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
				SRVSystem(MotionDetector* const, SRVTimer* const, ISRVBaseState* const, AlarmFacade* const);

				~SRVSystem();

				void Start(const uint16_t&);

				void Stop();

				SRVTimer* GetTimer();

				ISRVBaseState* GetBaseState();

				AlarmFacade* GetAlarm();

			private:
				friend class ISRVState;

				//// State-specific behaviour
				void handleFrameWithMotion();
	
				void handleFrameWithNoMotion();

				//// State-independent behaviour
				void changeBaseState(ISRVBaseState*);
	
				void changeCurrentState(ISRVState*);

				void playAlertSound();

				void startAlarm();

				void startRecording();

				void stopAlarm();

				void stopRecording();


			//// Data
			private:
				MotionDetector* m_p_motion_detector;

				AlarmFacade* m_alarm_facade_ptr;

				SRVTimer* m_p_timer;

				ISRVBaseState* m_p_base_system_state;

				ISRVState* m_p_current_system_state;

				bool m_running_flag;

				zmq::context_t* m_context_ptr;
		};

	} // namespace srv
} // namespace hcv

#endif // SRV_SYSTEM_HPP
