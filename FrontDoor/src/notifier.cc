#include "notifier.hpp"

#include "macros.hpp"

#include <exception>

using namespace std;

namespace hcv
{
	/////////////////////
	Notifier::Notifier()
	{
		PRINT("Notifier constructed.");
	}

	/////////////////////
	Notifier::Notifier(const vector<string>& i_destinations) : m_destinations(i_destinations)
	{
		PRINT("Notifier constructed with parameters.");
	}

	/////////////////////
	RetVal Notifier::AddDestination(const string& i_destination)
	{
		try
		{
			if (i_destination.empty())
				throw RetVal::NOTOK;

			m_destinations.push_back(i_destination);

			if (m_destinations.back() != i_destination)
				throw RetVal::NOTOK;
		}
		catch (RetVal r)
		{
			PRINT("Exception in Notifier::AddDestination: " << r);
			return r;
		}

		return RetVal::OK;
	}

	/////////////////////
	RetVal Notifier::NotifyAlarm(const time_t& i_time)
	{
		return RetVal::NOTOK;
	}

	/////////////////////
	RetVal Notifier::NotifyAlert(const time_t& i_time)
	{
		return RetVal::NOTOK;
	}

	RetVal Notifier::GetDestination(const uint8_t& i_index, string* o_destination)
	{
		try
		{
			try
			{
				*o_destination = m_destinations.at(i_index);
			}
			catch (exception e)
			{
				PRINT(e);
				throw RetVal::NOTOK;
			}
		}
		catch (RetVal r)
		{
			PRINT("Exception in Notifier::GetDestination: " << r);
			return r;
		}
		
		return RetVal::OK;
	}


} // namespace hcv
