//#include "sound_controller.hpp"
#include "alarm.hpp"
#include "zmq_message.hpp"
#include <zmq.hpp>
#include <thread>
#include <iostream>

using namespace std;

int main()
{
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_PAIR);
	socket.connect(hcv::Alarm::GetAddress());

	thread thr(hcv::Alarm::Spawn, &context, "soundfile");

	zmq::message_t reply;
	hcv::ZMQMessage* message = new hcv::ZMQMessage();
	message->data = 1;
	cout << "message: " << message->data << endl;

	socket.send(message, sizeof(hcv::ZMQMessage));

	socket.recv(&reply);
	message = (hcv::ZMQMessage*)reply.data();
	cout << "Reply: " << message->data << endl;

	message->data = 0;
	socket.send(message, sizeof(hcv::ZMQMessage));

	socket.recv(&reply);
	message = (hcv::ZMQMessage*)reply.data();
	cout << "Reply: " << message->data << endl;

	thr.join();

	socket.close();
	context.close();

	return 0;
}
