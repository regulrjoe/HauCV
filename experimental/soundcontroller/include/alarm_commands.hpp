#ifndef ALARM_COMMANDS_HPP
#define ALARM_COMMANDS_HPP

#include "i_command.hpp"

namespace hcv
{
	class Alarm;

	////////////////////// AlarmCommand
	class AlarmCommand : public ICommand
	{
		public:
			AlarmCommand(Alarm*);
			virtual void Execute() = 0;

		protected:
			Alarm* m_alarm_ptr;
	};

	////////////////////// StartAlarmCommand
	class StartAlarmCommand : public AlarmCommand
	{
		public:
			StartAlarmCommand(Alarm*);
			void Execute();
	};

	////////////////////// StopAlarmCommand
	class StopAlarmCommand : public AlarmCommand
	{
		public:
			StopAlarmCommand(Alarm*);
			void Execute();
	};

	////////////////////// ShutdownAlarmCommand
	class ShutdownAlarmCommand : public AlarmCommand
	{
		public:
			ShutdownAlarmCommand(Alarm*);
			void Execute();
	};

} // namespace hcv

#endif // ALARM_COMMANDS_HPP

