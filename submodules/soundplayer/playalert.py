from playsound import playsound
import zmq

addr = 'tcp://127.0.0.1:1121'
context = zmq.Context()
socket = context.socket(zmq.REP)

socket.bind(addr)

# Sleep to allow sockets to connect.
time.sleep(1.0)

soundfile = 'smsalert.mp3'

while True:
    # Wait for next request from client
    message = socket.recv()
    print("Playing sound.")

    # Do the works
    playsound('sounds/'+soundfile)

    # Send reply back to client
    socket.send(b"0")
