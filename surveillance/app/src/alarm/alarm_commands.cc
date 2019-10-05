#include "alarm/alarm_commands.hpp"
#include "alarm/alarm.hpp"

#include "utils/macros.hpp"

#include <dbg.h>

using namespace std;

namespace hcv
{

	////////////////////////
	AlarmCommand::AlarmCommand(Alarm* i_alarm_ptr) : m_alarm_ptr(i_alarm_ptr)
	{
		dbg("AlarmCommand::AlarmCommand()");
		//printINFO("AlarmCommand Constructed");
	}

	/////////////////////////
	///////// START /////////
	/////////////////////////
	
	////////////////////////
	StartAlarmCommand::StartAlarmCommand(Alarm* i_alarm_ptr) : AlarmCommand(i_alarm_ptr)
	{
		dbg("StartAlarmCommand::StartAlarmCommand()");
		//printINFO("StartAlarmCommand Constructed");
	}

	////////////////////////
	void StartAlarmCommand::Execute()
	{
		dbg("StartAlarmCommand::Execute()");
		m_alarm_ptr->Start();
	}

	/////////////////////////
	///////// STOP //////////
	/////////////////////////
	
	////////////////////////
	StopAlarmCommand::StopAlarmCommand(Alarm* i_alarm_ptr) : AlarmCommand(i_alarm_ptr)
	{
		dbg("StopAlarmCommand::StopAlarmCommand()");
		//printINFO("StopAlarmCommand Constructed");
	}

	////////////////////////
	void StopAlarmCommand::Execute()
	{
		dbg("StopAlarmCommand::Execute()");
		m_alarm_ptr->Stop();
	}

	/////////////////////////
	/////// SHUTDOWN ////////
	/////////////////////////
	
	////////////////////////
	ShutdownAlarmCommand::ShutdownAlarmCommand(Alarm* i_alarm_ptr) : AlarmCommand(i_alarm_ptr)
	{
		dbg("ShutdownAlarmCommand::ShutdownAlarmCommand()");
		//printINFO("ShutdownAlarmCommand Constructed");
	}

	////////////////////////
	void ShutdownAlarmCommand::Execute()
	{
		dbg("ShutdownAlarmCommand::Execute()");
		m_alarm_ptr->Shutdown();
	}

	/////////////////////////////////
	/////// UPDATE SOUNDFILE ////////
	/////////////////////////////////
	
	////////////////////////
	UpdateSoundfileAlarmCommand::UpdateSoundfileAlarmCommand(Alarm* i_alarm_ptr, const string& i_soundfile) : m_soundfile(i_soundfile), AlarmCommand(i_alarm_ptr)
	{
		dbg("UpdateSoundfileAlarmCommand::UpdateSoundfileAlarmCommand()");
		//printINFO("UpdateSoundfileAlarmCommand Constructed with soundfile " << i_soundfile);
	}

	////////////////////////
	void UpdateSoundfileAlarmCommand::Execute()
	{
		dbg("UpdateSoundfileAlarmCommand::Execute()");
		m_alarm_ptr->SetSoundfile(m_soundfile);
	}

} // namespace hcv
