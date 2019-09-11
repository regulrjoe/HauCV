from playsound import playsound
import time
import zmq

sound = ''
on_flag = False
shutdown_flag = False

on_addr = 'tcp://127.0.0.1:1111'
off_addr = 'tcp://127.0.0.1:1112'
shutdown_addr = 'tcp://127.0.0.1:1110'

context = zmq.Context()
on_socket = context.socket(zmq.REP)
off_socket = context.socket(zmq.REP)
shutdown_socket = context.socket(zmq.REP)

on_socket.bind(on_addr)
off_socket.bind(off_addr)
shutdown_socket.bind(shutdown_addr)

# Initialize poll set
poller = zmq.Poller()
poller.register(on_socket, zmq.POLLIN)
poller.register(off_socket, zmq.POLLIN)
poller.register(shutdown_socket, zmq.POLLIN)

# Sleep to allow sockets to connect.
time.sleep(1.0)

def turn_on(soundfile):
    global sound
    global on_flag
    sound = soundfile.decode('utf-8')
    on_flag = True
    on_socket.send(b'0')
    print("Turning Alarm ON with sound: %s." % soundfile)


def turn_off():
    global on_flag
    on_flag = False
    off_socket.send(b'0')
    print("Turning Alarm OFF.")


def shutdown():
    global on_flag
    global shutdown_flag
    on_flag = False
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
        if on_socket in socks:
            message = on_socket.recv()
            turn_on(message)
        if off_socket in socks:
            message = off_socket.recv()
            turn_off()
        if shutdown_socket in socks:
            message = shutdown_socket.recv()
            shutdown()

        # Do the works.
        if shutdown_flag is True:
            break
        elif on_flag is True:
            playsound('sounds/'+sound)
        else:
            time.sleep(1)

    print("Bye bye.")

if __name__ == "__main__":
        main()
