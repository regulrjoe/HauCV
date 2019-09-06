#include "notifier.hpp"

#include "macros.hpp"
#include "retval.hpp"

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
	void Notifier::AddDestination(const string& i_destination)
	{
		try
		{
			if (i_destination.empty())
				throw RetVal::NotOK;

			m_destinations.push_back(i_destination);

			if (m_destinations.back() != i_destination)
				throw RetVal::NotOK;
		}
		catch (const RetVal& rv)
		{
			PRINT("Exception in Notifier::AddDestination: " << r);
			throw rv;
		}
	}

	/////////////////////
	void Notifier::NotifyAlarm(const time_t& i_time)
	{
		// TODO.
	}

	/////////////////////
	void Notifier::NotifyAlert(const time_t& i_time)
	{
		// TODO.
	}

	void Notifier::GetDestination(const uint8_t& i_index, string* o_destination)
	{
		try
		{
			*o_destination = m_destinations.at(i_index);
		}
		catch (const exception& e)
		{
			throw e;
		}
	}


} // namespace hcv
