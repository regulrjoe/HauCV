#include "soundcontroller/alarm_commands.hpp"
#include "soundcontroller/alarm.hpp"

//#include "macros.hpp"

#include <dbg.h>

#include <iostream>

using namespace std;

namespace hcv
{

	////////////////////////
	AlarmCommand::AlarmCommand(Alarm* i_alarm_ptr) : m_alarm_ptr(i_alarm_ptr)
	{
		dbg("AlarmCommand Constructed.");
		dbg(i_alarm_ptr);
		//PRINT("AlarmCommand Constructed.");
	}

	///////// START ////////
	
	////////////////////////
	StartAlarmCommand::StartAlarmCommand(Alarm* i_alarm_ptr) : AlarmCommand(i_alarm_ptr)
	{
		dbg("StartAlarmCommand Constructed.");
		dbg(i_alarm_ptr);
		//PRINT("StartAlarmCommand Constructed.");
	}

	////////////////////////
	void StartAlarmCommand::Execute()
	{
		m_alarm_ptr->start();
	}

	////////// STOP /////////
	
	////////////////////////
	StopAlarmCommand::StopAlarmCommand(Alarm* i_alarm_ptr) : AlarmCommand(i_alarm_ptr)
	{
		dbg("StopAlarmCommand Constructed.");
		dbg(i_alarm_ptr);
		//PRINT("StopAlarmCommand Constructed.");
	}

	////////////////////////
	void StopAlarmCommand::Execute()
	{
		m_alarm_ptr->stop();
	}

	/////// SHUTDOWN ////////
	
	////////////////////////
	ShutdownAlarmCommand::ShutdownAlarmCommand(Alarm* i_alarm_ptr) : AlarmCommand(i_alarm_ptr)
	{
		dbg("ShutdownAlarmCommand Constructed.");
		dbg(i_alarm_ptr);
		//PRINT("ShutdownAlarmCommand Constructed.");
	}

	////////////////////////
	void ShutdownAlarmCommand::Execute()
	{
		m_alarm_ptr->shutdown();
	}

} // namespace hcv
