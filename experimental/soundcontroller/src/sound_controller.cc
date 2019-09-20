#include "sound_controller.hpp"

#include <iostream>

using namespace std;

namespace hcv
{
	/////////////////////////
	SoundController::SoundController()
	{
		m_addr = "inproc://soundctrl";
		m_alarm_playing = false;
	}

	/////////////////////////
	SoundController::~SoundController()
	{
	}

	////////////////////////
	void SoundController::Init(zmq::context_t* i_context)
	{
		m_context = i_context;
		m_socket = new zmq::socket_t(*m_context, ZMQ_PAIR);
		m_socket->bind(m_addr);

		m_items[0] = { static_cast<void*>(m_socket), 0, ZMQ_POLLIN, 0 };

		SoundController::doProcess();
	}

	/////////////////////////
	string SoundController::GetAddr()
	{
		return m_addr;
	}

	/////////////////////////
	void SoundController::doProcess()
	{
		cout << "doProcess" << endl;

		zmq::message_t request;
		IntMessage* request_msg;
		zmq::message_t reply(sizeof(IntMessage));

		while (true)
		{
			int ret = zmq::poll(&m_items[0], 1, 0);

			if (ret < 0)
			{
				IntMessage msg;
				msg.data = -1;
				//memcpy(IntMessage(-1), request.data(), sizeof(int));
				m_socket->send(&msg, sizeof(IntMessage));
			}

			// If there is an event.
			if (m_items[0].revents & ZMQ_POLLIN)
			{
				m_socket->recv(&request);
				request_msg = (IntMessage*)request.data();


				if (request_msg->data == 0) // Shutdown
				{
					break;
				}
				else if (request_msg->data == 1) // Play Alert
				{
					try
					{
						doPlayAlert();
						//memcpy(reply.data(), request.data(), sizeof(int));
						m_socket->send(&request_msg, sizeof(IntMessage));
					}
					catch (...)
					{
						//memcpy(-1, request.data(), sizeof(int));
						//m_socket->send(reply);

						IntMessage msg;
						msg.data = -1;
						m_socket->send(&msg, sizeof(IntMessage));
					}
				}
				else if (request_msg->data == 2) // Start Alarm
				{
					doStartAlarm();
					//memcpy(reply.data(), request.data(), sizeof(int));
					//m_socket->send(reply);
					m_socket->send(&request_msg, sizeof(IntMessage));
				}
				else if (request_msg->data == 3) // Stop Alarm
				{
					doStopAlarm();
					//memcpy(reply.data(), request.data(), sizeof(int));
					//m_socket->send(reply);
					m_socket->send(&request_msg, sizeof(IntMessage));
				}
				else
				{
					//memcpy(-1, request.data(), sizeof(int));
					//m_socket->send(reply);

					IntMessage msg;
					msg.data = -1;
					m_socket->send(&msg, sizeof(IntMessage));
				}
			}

			// Actual continuous process.
			if (m_alarm_playing)
				doPlayAlarm();
		}
		
		//memcpy(reply.data(), request.data(), sizeof(int));
		//m_socket->send(reply);
		m_socket->send(&request_msg, sizeof(IntMessage));
	}

	/////////////////////////
	void SoundController::doPlayAlert()
	{
		cout << "doPlayAlert" << endl;
	}

	/////////////////////////
	void SoundController::doPlayAlarm()
	{
		cout << "doPlayAlarm" << endl;
	}

	/////////////////////////
	void SoundController::doStartAlarm()
	{
		cout << "doStartAlarm" << endl;
		m_alarm_playing = true;
	}

	/////////////////////////
	void SoundController::doStopAlarm()
	{
		cout << "doStopAlarm" << endl;
		m_alarm_playing = false;
	}

} // namespace hcv

