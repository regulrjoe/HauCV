#ifndef fd_state_hpp
#define fd_state_hpp

#include "fd_system.hpp"

namespace hcv
{
	//////////////////////
	class IFDState
	{
		public:
			virtual bool HandleBody(FDSystem&);
			
			virtual bool HandleNoBody(FDSystem&);

		protected:
			bool changeBaseState(FDSystem&, const IFDState*);

			bool changeCurrentState(FDSystem&, const IFDState*);
	};

	//////////////////////
	class IFDBaseState : virtual public IFDState
	{
		protected:
			bool startRecording(FDSystem&);
	};

	//////////////////////
	class IFDCurrentState : virtual public IFDState {};

	//////////////////////
	class AlertState : public IFDBaseState, public IFDCurrentState
	{
		public:
			static IFDState* Instance();
			static IFDBaseState* BInstance();
			static IFDCurrentState* CInstance();

		private:
			bool sendAlertNotification();

			bool playAlertSound();
	};

	//////////////////////
	class IdleState : public IFDBaseState, public IDFCurrentState
	{
		public:
			static IFDState* Instance();
			static IFDBaseState* BInstance();
			static IFDCurrentState* CInstance();
	};

	//////////////////////
	class RecordingState : public IFDCurrentState
	{
		public:
			static IFDState* Instance();
			static IFDCurrentState* CInstance();

		private:
			bool soundAlarm();

			bool sendAlarmNotification();

			bool stopRecording();

			bool storeVideo();
	};

	//////////////////////
	class RecordingAndAlarmingState : public IFDCurrentState
	{
		public:
			static IFDState* Instance();
			static IFDCurrentState* CInstance();

		private:
			bool stopAlarm();

			bool sendStoppedAlarmNotification();
	};

} // namespace hcv

#endif // fd_state_hpp
