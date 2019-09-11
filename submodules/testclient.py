import sys
import time
import zmq

context = zmq.Context()

if len(sys.argv) < 3:
    print("Usage:\n\tpython3 testclient <module> <cmd>\nExample:\n\tpython3 testclient alarm on")
else:
    if (sys.argv[1] == 'alarm'):
        if (sys.argv[2] == 'on'):
            alarm_on_socket = context.socket(zmq.REQ)
            alarm_on_socket.connect("tcp://localhost:1111")
            alarm_on_socket.send(b"smsalert.mp3")
            message = alarm_on_socket.recv()
            assert(message == b'0')

        elif (sys.argv[2] == 'off'):
            alarm_off_socket = context.socket(zmq.REQ)
            alarm_off_socket.connect("tcp://localhost:1112")
            alarm_off_socket.send(b"0")
            message = ''
            message = alarm_off_socket.recv()
            assert(message == b'0')

        elif (sys.argv[2] == 'shutdown'):
            alarm_shutdown_socket = context.socket(zmq.REQ)
            alarm_shutdown_socket.connect("tcp://localhost:1110")
            alarm_shutdown_socket.send(b"0")
            message = ''
            message = alarm_shutdown_socket.recv()
            assert(message == b'0')

        else:
            print("Unrecognized command.")

    elif (sys.argv[1] == 'alert'):
        if (sys.argv[2] == 'play'):
            alert_play_socket = context.socket(zmq.REQ)
            alert_play_socket.connect("tcp://localhost:1121")
            alert_play_socket.send(b"smsalert.mp3")
            message = alert_play_socket.recv()
            assert(message == b'0')

        elif (sys.argv[2] == 'shutdown'):
            alert_shutdown_socket = context.socket(zmq.REQ)
            alert_shutdown_socket.connect("tcp://localhost:1120")
            alert_shutdown_socket.send(b'0')
            message = alert_shutdown_socket.recv()
            assert(message == b'0')

        else:
            print("Unrecognized command.")
    else:
        print("Unrecognized module.")
