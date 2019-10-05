#ifndef RCODE_HPP
#define RCODE_HPP

#include <string>

using namespace std;

namespace hcv
{
	enum class RCode
	{
		OK,
		NOTOK
	};

	class RCodeMsg
	{
		public:
			static const string GetMsg(const RCode& i_rc) { return m_messages[(int)i_rc]; }

		private:
			static const string m_messages[2];
	};

} // namespace hcv



#endif // RCODE_HPP
