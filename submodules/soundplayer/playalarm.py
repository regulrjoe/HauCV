from playsound import playsound
import time
import zmq

addr = 'tcp://127.0.0.1:1122'
context = zmq.Context()
socket = context.socket(zmq.REP)

socket.bind(addr)

# Sleep to allow sockets to connect.
time.sleep(1.0)

soundfile = 'smsalert.mp3'
is_on = False

while True:
    # Wait for next request from client
    try:
        message = socket.recv(zmq.NOBLOCK)
        print("MESSAGE RECEIVED.")

        # Turn off
        if message is b'0':
            socket.send(b'1')
            print("Shutting down Alarm Player.")
            break
        # Turn on
        elif message is b'1':
            is_on = True
            print("Alarm turned ON.")
            socket.send(b'1')
        # Shutdown
        elif message is b'2':
            is_on = False
            print("Alarm turned OFF.")
            socket.send(b'1')
        else:
            socket.send(b'0')
            print("Payload not recognized: %s" % message)

    except:
        print("No message received.")

    if is_on is True:
        print("Alarm is ON")
        playsound('sounds/'+soundfile)
    else:
        print("Alarm is OFF.")
        time.sleep(1)

print("Bye bye.")
