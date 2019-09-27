#ifndef NOTIFIER_HPP
#define NOTIFIER_HPP

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

			void AddDestination(const string&);

			void NotifyAlarm(const time_t&);

			void NotifyAlert(const time_t&);

			void GetDestination(const uint8_t&, string*);

		private:
			vector<string> m_destinations;
	};

} // namespace hcv
#endif // NOTIFIER_HPP
