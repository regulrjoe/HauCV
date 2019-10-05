#include "alarm/alarm.hpp"
#include "alarm/alarm_states.hpp"

#include "utils/rcode.hpp"
#include "utils/macros.hpp"

#include <dbg.h>

#include <chrono>
#include <thread>

#include <stdlib.h>

namespace hcv
{
		/////////////////////////////
		/////// IAlarmState /////////
		/////////////////////////////
		void IAlarmState::changeBaseState(Alarm* i_alarm_ptr, IAlarmState* i_alarm_state)
		{
			dbg("IAlarmState::changeBaseState()");
			try
			{
				i_alarm_ptr->changeState(i_alarm_state);
			}
			catch (const RCode& rc)
			{
				printERROR(RCMsg(rc));
				throw rc;
			}
			catch (const exception& e)
			{
				printERROR(e.what());
				throw e;
			}
		}

		/////////////////////////////
		////// ActiveAlarmState /////
		/////////////////////////////

		/////////////////////////////////
		ActiveAlarmState* ActiveAlarmState::singleton = 0;

		/////////////////////////////////
		IAlarmState* ActiveAlarmState::Instance()
		{
			dbg("ActiveAlarmState::Instance()");
			if (singleton == 0)
				singleton = new ActiveAlarmState();
			return singleton;
		}

		/////////////////////////////////
		void ActiveAlarmState::Play(Alarm* i_alarm_ptr)
		{
			dbg("ActiveAlarmState::Play()");
			string player = "mpg123 " + i_alarm_ptr->GetSoundfile();
			system(player.c_str());
		}

		/////////////////////////////////
		void ActiveAlarmState::Start(Alarm* i_alarm_ptr)
		{
			dbg("ActiveAlarmState::Start()");
			printINFO("Alarm is already Active."); // TODO change to printWARNGING.
			throw RCode::NOTOK; // TODO. Specify a better RCode.
		}

		/////////////////////////////////
		void ActiveAlarmState::Stop(Alarm* i_alarm_ptr)
		{
			dbg("ActiveAlarmState::Stop()");
			this->changeBaseState(i_alarm_ptr, InactiveAlarmState::Instance());
		}

		/////////////////////////////
		///// InactiveAlarmState ////
		/////////////////////////////

		/////////////////////////////////
		InactiveAlarmState* InactiveAlarmState::singleton = 0;

		/////////////////////////////////
		IAlarmState* InactiveAlarmState::Instance()
		{
			dbg("InactiveAlarmState::Instance()");
			if (singleton == 0)
				singleton = new InactiveAlarmState();
			return singleton;
		}

		/////////////////////////////////
		void InactiveAlarmState::Play(Alarm* i_alarm_ptr)
		{
			this_thread::sleep_for(chrono::milliseconds(1000));
		}

		/////////////////////////////////
		void InactiveAlarmState::Start(Alarm* i_alarm_ptr)
		{
			dbg("InactiveAlarmState::Start()");
			this->changeBaseState(i_alarm_ptr, ActiveAlarmState::Instance());
		}

		/////////////////////////////////
		void InactiveAlarmState::Stop(Alarm* i_alarm_ptr)
		{
			dbg("InactiveAlarmState::Stop()");
			printINFO("Alarm is already Inactive."); // TODO change to printWARNGING.
			throw RCode::NOTOK; // TODO. Specify a better RCode.
		}

} // namespace
