#ifndef ZMQ_CONFIG_HPP
#define ZMQ_CONFIG_HPP

#include <zmq.hpp>
#include <string>

namespace hcv
{
	struct ZMQConfig
	{
		zmq::context_t* context;
		zmq::socket_t* socket;
		std::string address;
	};

} // namespace hcv

#endif // ZMQ_CONFIG_HPP
