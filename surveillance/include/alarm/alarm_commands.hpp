#ifndef ALARM_COMMANDS_HPP
#define ALARM_COMMANDS_HPP

#include "i_command.hpp"

#include <string>

namespace hcv
{
	class Alarm;

	////////////////////// AlarmCommand
	class AlarmCommand : public ICommand
	{
		public:
			virtual void Execute() = 0;
			virtual ~AlarmCommand() {};

		protected:
			AlarmCommand(Alarm*);
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
	
	////////////////////// UpdateSoundfileAlarmCommand
	class UpdateSoundfileAlarmCommand : public AlarmCommand
	{
		public:
			UpdateSoundfileAlarmCommand(Alarm*, const std::string&);
			void Execute();

		private:
			std::string m_soundfile;
	};

} // namespace hcv

#endif // ALARM_COMMANDS_HPP

