#include "alarm_commands.hpp"

//#include "macros.hpp"

#include <iostream>

using namespace std;

namespace hcv
{
	///////// START ////////
	
	////////////////////////
	StartAlarmCommand::StartAlarmCommand(Alarm* i_alarm_ptr) : m_alarm_ptr(i_alarm_ptr)
	{
		//PRINT("StartAlarmCommand Constructed.");
	}

	////////////////////////
	StartAlarmCommand::Execute()
	{
		m_alarm_ptr->start();
	}

	////////// STOP /////////
	
	////////////////////////
	StopAlarmCommand::StopAlarmCommand(Alarm* i_alarm_ptr) : m_alarm_ptr(i_alarm_ptr)
	{
		//PRINT("StopAlarmCommand Constructed.");
	}

	////////////////////////
	StopAlarmCommand::Execute()
	{
		m_alarm_ptr->stop();
	}

	/////// SHUTDOWN ////////
	
	////////////////////////
	ShutdownAlarmCommand::ShutdownAlarmCommand(Alarm* i_alarm_ptr) : m_alarm_ptr(i_alarm_ptr)
	{
		//PRINT("ShutdownAlarmCommand Constructed.");
	}

	////////////////////////
	ShutdownAlarmCommand::Execute()
	{
		m_alarm_ptr->shutdown();
	}

} // namespace hcv
