#include "sound_controller.hpp"

#include "macros.hpp"
#include "retval.hpp"

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
	void SoundController::SoundAlarm()
	{
		// TODO.
		m_alarm_is_on = true;
	}

	////////////////////
	void SoundController::SoundAlert()
	{
		// TODO.
	}

	////////////////////
	void SoundController::StopAlarm()
	{
		//TODO.
		m_alarm_is_on = false;
	}

} // namespace hcv

