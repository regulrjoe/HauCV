#include "srv/states.hpp"

#include "macros.hpp"
#include "rcode.hpp"

namespace hcv
{
	namespace srv
	{

		/////////////////////////////
		ISRVState::~ISRVState() {}

		/////////////////////////////
		void ISRVState::HandleMotion(SRVSystem* i_system)
		{
			// Do nothing.
		}

		/////////////////////////////
		void ISRVState::HandleNoMotion(SRVSystem* i_system)
		{
			// Do nothing.
		}

		/////////////////////////////
		void ISRVState::changeBaseState(SRVSystem* i_system, ISRVBaseState* i_base_state)
		{
			try
			{
				i_system->changeBaseState(i_base_state);
			}
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				throw rc;
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				throw e;
			}
		}

		/////////////////////////////
		void ISRVState::changeCurrentState(SRVSystem* i_system, ISRVState* i_state)
		{
			try
			{
				i_system->changeCurrentState(i_state);
			}
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				throw rc;
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				throw e;
			}
		}

		/////////////////////////////
		void ISRVState::playAlertSound(SRVSystem* i_system)
		{
			try
			{
				i_system->playAlertSound();
			}
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				throw rc;
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				throw e;
			}
		}

		/////////////////////////////
		void ISRVState::soundAlarm(SRVSystem* i_system)
		{
			try
			{
				i_system->startAlarm();
			}
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				throw rc;
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				throw e;
			}
		}

		/////////////////////////////
		void ISRVState::startRecording(SRVSystem* i_system)
		{
			try
			{
				i_system->startRecording();
			}
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				throw rc;
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				throw e;
			}
		}

		/////////////////////////////
		void ISRVState::stopAlarm(SRVSystem* i_system)
		{
			try
			{
				i_system->stopAlarm();
			}
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				throw rc;
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				throw e;
			}
		}

		/////////////////////////////
		void ISRVState::stopRecording(SRVSystem* i_system)
		{
			try
			{
				i_system->stopRecording();
			}
			catch (const RCode& rc)
			{
				PRINTERR(rc);
				throw rc;
			}
			catch (const exception& e)
			{
				PRINTEXC(e);
				throw e;
			}
		}

	} // namespace srv
} // namespace hcv
