#ifndef ALARM_STATES_HPP
#define ALARM_STATES_HPP


namespace hcv
{
	class Alarm;
	
	////////////////////// IAlarmState
	class IAlarmState
	{
		public:
			virtual void Play(Alarm*) = 0;
			virtual void Start(Alarm*) = 0;
			virtual void Stop(Alarm*) = 0;

		protected:
			void changeBaseState(Alarm*, IAlarmState*);
	};

	////////////////////// ActiveAlarmState
	class ActiveAlarmState : public IAlarmState
	{
		public:
			virtual void Play(Alarm*);
			virtual void Start(Alarm*);
			virtual void Stop(Alarm*);

			static IAlarmState* Instance();

		private:
			ActiveAlarmState() {}
		private:
			static ActiveAlarmState* singleton;
	};

	////////////////////// InactiveAlarmState
	class InactiveAlarmState : public IAlarmState
	{
		public:
			virtual void Play(Alarm*);
			virtual void Start(Alarm*);
			virtual void Stop(Alarm*);

			static IAlarmState* Instance();

		private:
			InactiveAlarmState() {}
		private:
			static InactiveAlarmState* singleton;
	};

} // namespace hcv

#endif // ALARM_STATES_HPP
