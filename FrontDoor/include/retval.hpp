#ifndef RETVAL_HPP
#define RETVAL_HPP

#include <string>

using namespace std;

namespace hcv
{
	enum class RetVal
	{
		OK,
		NOTOK
	};

	class RetValMsg
	{
		public:
			static const string GetMsg(const RetVal& i_val) { return m_messages[(int)i_val]; }

		private:
			static const string m_messages[2];
	};

	const string RetValMsg::m_messages[] = 
	{
		/* OK */	"All OK.",
		/* NOTOK */	"All not OK."
	};

} // namespace hcv



#endif // RETVAL_HPP
