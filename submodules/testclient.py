import sys
import time
import zmq

context = zmq.Context()

if len(sys.argv) < 3:
    print("Usage:\n\tpython3 testclient <module> <cmd>\nExample:\n\tpython3 testclient alarm start")
else:
    if (sys.argv[1] == 'alarm'):
        if (sys.argv[2] == 'start'):
            start_alarm_socket = context.socket(zmq.REQ)
            start_alarm_socket.connect("tcp://localhost:1111")
            start_alarm_socket.send(b"smsalert.mp3")
            message = start_alarm_socket.recv()
            assert(message == b'0')

        elif (sys.argv[2] == 'stop'):
            stop_alarm_socket = context.socket(zmq.REQ)
            stop_alarm_socket.connect("tcp://localhost:1112")
            stop_alarm_socket.send(b"0")
            message = ''
            message = stop_alarm_socket.recv()
            assert(message == b'0')

        elif (sys.argv[2] == 'shutdown'):
            shutdown_alarm_socket = context.socket(zmq.REQ)
            shutdown_alarm_socket.connect("tcp://localhost:1110")
            shutdown_alarm_socket.send(b"0")
            message = ''
            message = shutdown_alarm_socket.recv()
            assert(message == b'0')

        else:
            print("Unrecognized command.")

    elif (sys.argv[1] == 'alert'):
        if (sys.argv[2] == 'play'):
            play_alert_socket = context.socket(zmq.REQ)
            play_alert_socket.connect("tcp://localhost:1121")
            play_alert_socket.send(b"smsalert.mp3")
            message = play_alert_socket.recv()
            assert(message == b'0')

        elif (sys.argv[2] == 'shutdown'):
            shutdown_alert_socket = context.socket(zmq.REQ)
            shutdown_alert_socket.connect("tcp://localhost:1120")
            shutdown_alert_socket.send(b'0')
            message = shutdown_alert_socket.recv()
            assert(message == b'0')

        else:
            print("Unrecognized command.")
    else:
        print("Unrecognized module.")
