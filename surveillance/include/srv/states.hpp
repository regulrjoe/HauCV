#ifndef SRV_STATES_HPP
#define SRV_STATES_HPP

#include "srv/system.hpp"

namespace hcv
{
	namespace srv
	{

		class SRVSystem;
		class ISRVBaseState;
		
		////////////////////// ISRVState
		class ISRVState
		{
			public:
				virtual ~ISRVState() = 0;
				virtual void HandleFrameWithMotion(SRVSystem*) = 0;
				virtual void HandleFrameWithNoMotion(SRVSystem*) = 0;

			protected:
				void changeBaseState(SRVSystem*, ISRVBaseState*);
				void changeCurrentState(SRVSystem*, ISRVState*);
		};

		////////////////////// ISRVBaseState
		class ISRVBaseState : public ISRVState
		{
			public:
				virtual ~ISRVBaseState() = 0;
		};

		////////////////////// AlertState
		class AlertState : public ISRVBaseState
		{
			public:
				static ISRVState* Instance();
				static ISRVBaseState* InstanceAsBase();

				void HandleFrameWithMotion(SRVSystem*);
				void HandleFrameWithNoMotion(SRVSystem*);

			private:
				AlertState() {}
			
			private:
				static AlertState* singleton;
		};

		////////////////////// IdleState
		class IdleState : public ISRVBaseState
		{
			public:
				IdleState() {}
				static ISRVState* Instance();
				static ISRVBaseState* InstanceAsBase();
				
				void HandleFrameWithMotion(SRVSystem*);
				void HandleFrameWithNoMotion(SRVSystem*);

			private:
				static IdleState* singleton;
		};

		////////////////////// RecordingState
		class RecordingState : public ISRVState
		{
			public:
				static ISRVState* Instance();

				void HandleFrameWithMotion(SRVSystem*);
				void HandleFrameWithNoMotion(SRVSystem*);

			private:
				RecordingState() {}

			private:
				static RecordingState* singleton;
		};

		////////////////////// AlarmingState
		class AlarmingState : public ISRVState
		{
			public:
				static ISRVState* Instance();

				void HandleFrameWithMotion(SRVSystem*);
				void HandleFrameWithNoMotion(SRVSystem*);

			private:
				AlarmingState() {}

			private:
				static AlarmingState* singleton;
		};

		////////////////////// RecordingAndAlarmingState
		class RecordingAndAlarmingState : public ISRVState
		{
			public:
				static ISRVState* Instance();

				void HandleFrameWithMotion(SRVSystem*);
				void HandleFrameWithNoMotion(SRVSystem*);

			private:
				RecordingAndAlarmingState() {}

			private:
				static RecordingAndAlarmingState* singleton;
		};

	} // namespace srv
} // namespace hcv

#endif // SRV_STATES_HPP
