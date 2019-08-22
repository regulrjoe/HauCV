#ifndef FD_SYSTEM_HPP
#define FD_SYSTEM_HPP

#include "body_detector.hpp"
#include "fd_state.hpp"
#include "fd_timers.hpp"

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
			FDSystem(BodyDetector* const, IFDBaseState* const, FDTimers* const);

			~FDSystem();

			bool Start(const int&);

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
//			bool triggerAlarm();
//
//			bool stopAlarm();
//
//			bool stopRecording();

		//// Data
		private:
			BodyDetector* m_p_body_detector;

			IFDBaseState* m_p_base_system_state;

			IFDState* m_p_current_system_state;

			vector<string> m_notification_destinations;

			FDTimers* m_p_timers;
	};
} // namespace hcv

#endif // FD_SYSTEM_HPP
