#ifndef SRV_STATE_HPP
#define SRV_STATE_HPP

#include "srv/system.hpp"

#include "retval.hpp"

namespace hcv
{
	namespace srv
	{

		class SRVSystem;
		class ISRVBaseState;
		
		//////////////////////
		class ISRVState
		{
			public:
				virtual RetVal HandleMotion(SRVSystem*) = 0;
				virtual RetVal HandleNoMotion(SRVSystem*) = 0;

			protected:
				RetVal changeBaseState(SRVSystem*, ISRVBaseState*);
				RetVal changeCurrentState(SRVSystem*, ISRVState*);
		};

		//////////////////////
		class ISRVBaseState : public ISRVState
		{
			public:
				virtual ~ISRVBaseState() = 0;
			protected:
				RetVal startRecording(SRVSystem*);
		};

		//////////////////////
		class AlertState : public ISRVBaseState
		{
			public:
				static ISRVState* Instance();
				static ISRVBaseState* InstanceAsBase();
				RetVal HandleMotion(SRVSystem*);
				RetVal HandleNoMotion(SRVSystem*);

			private:
				AlertState() {}
				RetVal playAlertSound();
			
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
				RetVal HandleMotion(SRVSystem*);
				RetVal HandleNoMotion(SRVSystem*);

			private:
				static IdleState* singleton;
		};

		//////////////////////
		class RecordingState : public ISRVState
		{
			public:
				static ISRVState* Instance();
				RetVal HandleMotion(SRVSystem*);
				RetVal HandleNoMotion(SRVSystem*);

			private:
				RecordingState() {}
				RetVal soundAlarm();
				RetVal stopRecording();
				RetVal storeVideo();

			private:
				static RecordingState* singleton;
		};

		//////////////////////
		class AlarmingState : public ISRVState
		{
			public:
				static ISRVState* Instance();
				RetVal HandleMotion(SRVSystem*);
				RetVal HandleNoMotion(SRVSystem*);

			private:
				AlarmingState() {}
				RetVal startRecording();
				RetVal stopAlarm();

			private:
				static AlarmingState* singleton;
		};

		//////////////////////
		class RecordingAndAlarmingState : public ISRVState
		{
			public:
				static ISRVState* Instance();
				RetVal HandleMotion(SRVSystem*);
				RetVal HandleNoMotion(SRVSystem*);

			private:
				RecordingAndAlarmingState() {}
				RetVal stopAlarm();

			private:
				static RecordingAndAlarmingState* singleton;
		};

	} // namespace srv
} // namespace hcv

#endif // SRV_STATE_HPP
