#include "notifier.hpp"

#include "macros.hpp"

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
			m_destinations.push_back(i_destination);
			throw RetVal::NOTOK;
		}
		catch (RetVal r)
		{
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

} // namespace hcv
