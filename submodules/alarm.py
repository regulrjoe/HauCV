from playsound import playsound
import time
import zmq

soundfile = ''
playing_flag = False
shutdown_flag = False

start_addr = 'tcp://127.0.0.1:1111'
stop_addr = 'tcp://127.0.0.1:1112'
shutdown_addr = 'tcp://127.0.0.1:1110'

context = zmq.Context()
start_socket = context.socket(zmq.REP)
stop_socket = context.socket(zmq.REP)
shutdown_socket = context.socket(zmq.REP)

start_socket.bind(start_addr)
stop_socket.bind(stop_addr)
shutdown_socket.bind(shutdown_addr)

# Initialize poll set
poller = zmq.Poller()
poller.register(start_socket, zmq.POLLIN)
poller.register(stop_socket, zmq.POLLIN)
poller.register(shutdown_socket, zmq.POLLIN)

# Sleep to allow sockets to connect.
time.sleep(1.0)

def start(i_soundfile):
    global soundfile
    global playing_flag
    soundfile = i_soundfile.decode('utf-8')
    playing_flag = True
    start_socket.send(b'0')
    print("Starting Alarm with sound: %s." % soundfile)


def stop():
    global playing_flag
    playing_flag = False
    stop_socket.send(b'0')
    print("Stoping Alarm.")


def shutdown():
    global playing_flag
    global shutdown_flag
    playing_flag = False
    shutdown_flag = True
    shutdown_socket.send(b'0')
    print("Shutting Alarm down.")


def main():
    while True:
        try:
            socks = dict(poller.poll(timeout=1))
        except KeyboardInterrupt:
            break

        # Check for messages in sockets.
        if start_socket in socks:
            message = start_socket.recv()
            start(message)
        if stop_socket in socks:
            message = stop_socket.recv()
            stop()
        if shutdown_socket in socks:
            message = shutdown_socket.recv()
            shutdown()

        # Do the works.
        if shutdown_flag is True:
            break
        elif playing_flag is True:
            playsound('sounds/'+soundfile)
        else:
            time.sleep(1)

    print("Bye bye.")

if __name__ == "__main__":
        main()
