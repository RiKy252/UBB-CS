import socket
import threading
import random
import struct
import time

random.seed()
start = 1
end = 2**17 - 1
my_float = random.uniform(start, end)
print("Server float: ", my_float)
myLock = threading.Lock()
winnerThread = 0
e = threading.Event()
e.clear()
threads = []
clientCount = 0
difference = 0
minim = 2 ** 17


def worker(cs):
    global myLock, my_float, winnerThread, clientCount, e, minim, difference
    myIdCount = clientCount
    try:
        if True:
            clientFloat = cs.recv(4)
            clientFloat = struct.unpack('!f', clientFloat)[0]
            print(clientFloat)
            with myLock:
                localDifference = abs(my_float - clientFloat)
                if localDifference < minim:
                     minim = localDifference
                     winnerThread = threading.get_ident()
                     difference = localDifference
    except socket.timeout:
        print("No data received from client for 10 seconds. Closing connection...")
    except struct.error:
        print("Error in struct.unpack")
    e.wait()
    if threading.get_ident() == winnerThread:
        print('We have a winner', cs.getpeername())
        print('Thread ', myIdCount, ' winner')
        cs.sendall(b'You won!')
        e.set()
    else:
        cs.sendall(b'You lost!')

    time.sleep(1)
    cs.close()
    print("Worker Thread ", myIdCount, " ended")


def resetSrv():
    global myLock, winnerThread, my_float, threads, e, clientCount, minim, difference
    while True:
        e.wait()
        for t in threads:
            t.join()
        print("all threads are done")
        e.clear()
        myLock.acquire()
        threads = []
        winnerThread = -1
        clientCount = 0
        my_float = random.uniform(start, end)
        difference = 0
        minim = 2**17
        myLock.release()


if __name__ == '__main__':
    try:
        rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # rs.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        rs.settimeout(10)
        rs.bind(('0.0.0.0', 1234))
        rs.listen(5)
    except socket.error as msg:
        print(msg.strerror)
        exit(-1)
    t = threading.Thread(target=resetSrv, daemon=True)
    t.start()
    while True:
        try:
            print("Wait for number")
            client_socket, addr = rs.accept()
            print(f"Connection from {addr}")
            t = threading.Thread(target=worker, args=(client_socket,))
            threads.append(t)
            clientCount += 1
            t.start()
        except socket.timeout:
            print("Time's up")
            e.set()
