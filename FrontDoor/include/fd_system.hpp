#ifndef fd_system_hpp
#define fd_system_hpp

#include "body_detector.hpp"
#include "fd_state.hpp"

#include <cstdint>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

namespace hcv
{
	class IFDState;
	class IFDBaseState;

	class FDSystem
	{
		//// Methods
		public:
			FDSystem(BodyDetector* const, IFDBaseState* const, const uint8_t&, const uint8_t&, const uint8_t&);

			~FDSystem();

//			bool Start();
//
//			bool Stop();

		private:
			friend class IFDState;

//			bool changeBaseState(const IFDBaseState*);
//
//			bool changeCurrentState(const IFDState*);
//
//			bool playAlertSound();
//
//			bool sendNotification(const string&);
//
//			bool isTimeToTriggerAlarm();
//
//			bool isTimeToStopAlarm();
//
//			bool isTimeToStopRecording();

		//// Variables
		private:
			BodyDetector* m_body_detector;

			IFDBaseState* m_base_system_state;

			IFDState* m_current_system_state;

			uint8_t m_seconds_for_starting_alarm;

			uint8_t m_seconds_for_stopping_alarm;

			uint8_t m_seconds_for_stopping_recording;

			vector<string> m_notification_destinations;
			
			time_t m_last_body_first_detected;

			time_t m_last_body_last_detected;
	};
} // namespace hcv

#endif // fd_system_hpp
