#ifndef fd_state_hpp
#define fd_state_hpp

#include "fd_system.hpp"

namespace hcv
{
	class IFDBaseState;
	
	//////////////////////
	class IFDState
	{
		public:
			//virtual bool HandleBody(FDSystem&);
			//virtual bool HandleNoBody(FDSystem&);

		protected:
			//bool changeBaseState(FDSystem&, const IFDBaseState*);
			//bool changeCurrentState(FDSystem&, const IFDState*);
	};

	//////////////////////
	class IFDBaseState : public IFDState
	{
		protected:
			//bool startRecording(FDSystem&);
	};

	//////////////////////
	class AlertState : public IFDBaseState
	{
		public:
			static IFDState* Instance();
			static IFDBaseState* InstanceAsBase();

		private:
			AlertState() {}
//			bool sendAlertNotification();
//			bool playAlertSound();
		
		private:
			static AlertState* singleton;
	};

	//////////////////////
	class IdleState : public IFDBaseState
	{
		public:
			IdleState() {}
			static IFDState* Instance();
			static IFDBaseState* InstanceAsBase();

		private:
			static IdleState* singleton;
	};

	//////////////////////
	class RecordingState : public IFDState
	{
		public:
			static IFDState* Instance();

		private:
			RecordingState() {}
//			bool soundAlarm();
//			bool sendAlarmNotification();
//			bool stopRecording();
//			bool storeVideo();

		private:
			static RecordingState* singleton;
	};

	//////////////////////
	class RecordingAndAlarmingState : public IFDState
	{
		public:
			static IFDState* Instance();

		private:
			RecordingAndAlarmingState() {}
//			bool stopAlarm();
//			bool sendStoppedAlarmNotification();

		private:
			static RecordingAndAlarmingState* singleton;
	};

} // namespace hcv

#endif // fd_state_hpp
