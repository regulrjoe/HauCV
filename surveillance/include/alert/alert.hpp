#ifndef ALERT_HPP
#define ALERT_HPP

#include <string>

namespace hcv
{
	class Alert
	{
		public:
			Alert(const std::string&);
			~Alert();

			void Play();

		private:
			std::string m_soundfile;
	};

} // namespace hcv

#endif // ALERT_HPP
