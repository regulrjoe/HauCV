#ifndef NOTIFIER_HPP
#define NOTIFIER_HPP

#include "retval.hpp"

#include <string>
#include <vector>
#include <ctime>

using namespace std;

namespace hcv
{
	class Notifier
	{
		public:
			Notifier();

			Notifier(const vector<string>&);

			RetVal AddDestination(const string&);

			RetVal NotifyAlarm(const time_t&);

			RetVal NotifyAlert(const time_t&);

			RetVal GetDestination(const uint8_t&, string*);

		private:
			vector<string> m_destinations;
	};

} // namespace hcv
#endif // NOTIFIER_HPP
