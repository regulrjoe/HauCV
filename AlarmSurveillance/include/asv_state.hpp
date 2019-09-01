#ifndef ASV_STATE_HPP
#define ASV_STATE_HPP

#include "asv_system.hpp"

namespace hcv
{
	namespace asv
	{

		class IASVBaseState;
		
		//////////////////////
		class IASVState
		{
			public:
				//virtual bool HandleBody(ASVSystem&);
				//virtual bool HandleNoBody(ASVSystem&);

			protected:
				//bool changeBaseState(ASVSystem&, const IASVBaseState*);
				//bool changeCurrentState(ASVSystem&, const IASVState*);
		};

		//////////////////////
		class IASVBaseState : public IASVState
		{
			protected:
				//bool startRecording(ASVSystem&);
		};

		//////////////////////
		class AlertState : public IASVBaseState
		{
			public:
				static IASVState* Instance();
				static IASVBaseState* InstanceAsBase();

			private:
				AlertState() {}
	//			bool playAlertSound();
			
			private:
				static AlertState* singleton;
		};

		//////////////////////
		class IdleState : public IASVBaseState
		{
			public:
				IdleState() {}
				static IASVState* Instance();
				static IASVBaseState* InstanceAsBase();

			private:
				static IdleState* singleton;
		};

		//////////////////////
		class RecordingState : public IASVState
		{
			public:
				static IASVState* Instance();

			private:
				RecordingState() {}
	//			bool soundAlarm();
	//			bool stopRecording();
	//			bool storeVideo();

			private:
				static RecordingState* singleton;
		};

		//////////////////////
		class AlarmingState : public IASVState
		{
			public:
				static IASVState* Instance();

			private:
				AlarmingState() {}
	//			bool startRecording(ASVSystem&);
	//			bool stopAlarm(ASVSystem&);

			private:
				static AlarmingState* singleton;
		};

		//////////////////////
		class RecordingAndAlarmingState : public IASVState
		{
			public:
				static IASVState* Instance();

			private:
				RecordingAndAlarmingState() {}
	//			bool stopAlarm(ASVSystem&);

			private:
				static RecordingAndAlarmingState* singleton;
		};

	} // namespace asv
} // namespace hcv

#endif // ASV_STATE_HPP
