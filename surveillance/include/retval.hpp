#ifndef RETVAL_HPP
#define RETVAL_HPP

#include <string>

using namespace std;

namespace hcv
{
	enum class RetVal
	{
		OK,
		NotOK
	};

	class RetValMsg
	{
		public:
			static const string GetMsg(const RetVal& i_val) { return m_messages[(int)i_val]; }

		private:
			static const string m_messages[2];
	};

} // namespace hcv



#endif // RETVAL_HPP
