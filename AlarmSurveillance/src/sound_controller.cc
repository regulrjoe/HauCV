#include "sound_controller.hpp"

#include "macros.hpp"

namespace hcv
{

	////////////////////
	SoundController::SoundController() : m_alarm_is_on(false)
	{
		PRINT("SoundController empty constructed.");
	}

	////////////////////
	SoundController::SoundController(const SoundController& i_SoundController) :
		m_alarm_is_on(i_SoundController.m_alarm_is_on)
	{
		PRINT("SoundController constructed by copy.");
	}

	////////////////////
	SoundController::~SoundController()
	{
		PRINT("SoundController destroyed.");
	}
	
	////////////////////
	bool SoundController::IsAlarmOn()
	{
		return m_alarm_is_on;
	}

	////////////////////
	RetVal SoundController::SoundAlarm()
	{
		m_alarm_is_on = true;
		return RetVal::NOTOK;
	}

	////////////////////
	RetVal SoundController::SoundAlert()
	{
		return RetVal::NOTOK;
	}

	////////////////////
	RetVal SoundController::StopAlarm()
	{
		m_alarm_is_on = false;
		return RetVal::NOTOK;
	}

} // namespace hcv

