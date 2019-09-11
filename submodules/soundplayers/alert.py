from playsound import playsound
import time
import zmq

shutdown_flag = False

play_addr = 'tcp://127.0.0.1:1121'
shutdown_addr = 'tcp://127.0.0.1:1120'

context = zmq.Context()
play_socket = context.socket(zmq.REP)
shutdown_socket = context.socket(zmq.REP)

play_socket.bind(play_addr)
shutdown_socket.bind(shutdown_addr)

# Initialize poll set
poller = zmq.Poller()
poller.register(play_socket, zmq.POLLIN)
poller.register(shutdown_socket, zmq.POLLIN)

# Sleep to allow sockets to connect.
time.sleep(1.0)

def play(soundfile):
    try:
        print("Playing alert with sound: %s." % soundfile)
        playsound('sounds/'+soundfile.decode('utf-8'))
        play_socket.send(b'0')
    except:
        print("Error occurred at play().")
        play_socket.send(b'1')


def shutdown():
    global shutdown_flag
    print("Shutting down Alert.")
    shutdown_flag = True
    shutdown_socket.send(b'0')

def main():
    while True:
        try:
            socks = dict(poller.poll(timeout=1))
        except KeyboardInterrupt:
            break

        # Check for messages in sockets.
        if play_socket in socks:
            message = play_socket.recv()
            play(message)
        if shutdown_socket in socks:
            shutdown_socket.recv()
            shutdown()

        if shutdown_flag is True:
            break
        else:
            time.sleep(1)

    print("Bye bye.")

if __name__ == "__main__":
        main()

