#ifndef FD_STATE_HPP
#define FD_STATE_HPP

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
//			bool sendAlarmNotification();
//			bool soundAlarm();
//			bool stopRecording();
//			bool storeVideo();

		private:
			static RecordingState* singleton;
	};

	//////////////////////
	class AlarmingState : public IFDState
	{
		public:
			static IFDState* Instance();

		private:
			AlarmingState() {}
//			bool startRecording(FDSystem&);
//			bool stopAlarm(FDSystem&);

		private:
			static AlarmingState* singleton;
	};

	//////////////////////
	class RecordingAndAlarmingState : public IFDState
	{
		public:
			static IFDState* Instance();

		private:
			RecordingAndAlarmingState() {}
//			bool stopAlarm(FDSystem&);

		private:
			static RecordingAndAlarmingState* singleton;
	};

} // namespace hcv

#endif // FD_STATE_HPP
