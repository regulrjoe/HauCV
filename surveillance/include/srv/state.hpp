#ifndef SRV_STATE_HPP
#define SRV_STATE_HPP

#include "srv/system.hpp"

namespace hcv
{
	namespace srv
	{

		class ISRVBaseState;
		
		//////////////////////
		class ISRVState
		{
			public:
				//virtual bool HandleMotion(SRVSystem&);
				//virtual bool HandleNoMotion(SRVSystem&);

			protected:
				//bool changeBaseState(SRVSystem&, const ISRVBaseState*);
				//bool changeCurrentState(SRVSystem&, const ISRVState*);
		};

		//////////////////////
		class ISRVBaseState : public ISRVState
		{
			protected:
				//bool startRecording(SRVSystem&);
		};

		//////////////////////
		class AlertState : public ISRVBaseState
		{
			public:
				static ISRVState* Instance();
				static ISRVBaseState* InstanceAsBase();

			private:
				AlertState() {}
	//			bool playAlertSound();
			
			private:
				static AlertState* singleton;
		};

		//////////////////////
		class IdleState : public ISRVBaseState
		{
			public:
				IdleState() {}
				static ISRVState* Instance();
				static ISRVBaseState* InstanceAsBase();

			private:
				static IdleState* singleton;
		};

		//////////////////////
		class RecordingState : public ISRVState
		{
			public:
				static ISRVState* Instance();

			private:
				RecordingState() {}
	//			bool soundAlarm();
	//			bool stopRecording();
	//			bool storeVideo();

			private:
				static RecordingState* singleton;
		};

		//////////////////////
		class AlarmingState : public ISRVState
		{
			public:
				static ISRVState* Instance();

			private:
				AlarmingState() {}
	//			bool startRecording(SRVSystem&);
	//			bool stopAlarm(SRVSystem&);

			private:
				static AlarmingState* singleton;
		};

		//////////////////////
		class RecordingAndAlarmingState : public ISRVState
		{
			public:
				static ISRVState* Instance();

			private:
				RecordingAndAlarmingState() {}
	//			bool stopAlarm(SRVSystem&);

			private:
				static RecordingAndAlarmingState* singleton;
		};

	} // namespace srv
} // namespace hcv

#endif // SRV_STATE_HPP
