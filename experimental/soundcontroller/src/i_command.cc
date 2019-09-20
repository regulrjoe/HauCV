#include "commands.hpp"

#include "macros.hpp"
#include "rcode.hpp"

#include <iostream>

using namespace std;

namespace hcv
{

	////////////////////////
	ICommand::ICommand() {}

	////////////////////////
	ICommand::~ICommand() {}

	////////////////////////
	void ICommand::Execute()
	{
		try
		{
			m_p_socket->send(*m_p_request);

			zmq::message_t reply;
			m_p_socket->recv(&reply);
		}
		catch(const RCode& rc)
		{
			PRINTERR(rc);
		}
	}

} // namespace hcv
