import socket, struct, random, sys, time

if __name__ == '__main__':
    try:
        s = socket.create_connection(('127.0.0.1', 1234))
    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(-1)

    finished = False
    sr = float(1)
    er = float(2 ** 17 - 1)
    random.seed()

    my_num = random.uniform(sr, er)
    try:
        s.sendall(struct.pack('!f', my_num))
        print("I ve sent something...")
        answer = s.recv(1024)
        print("I ve received something...")
        print(answer.decode('ascii'))
    except socket.error as msg:
        print('Error: ', msg.strerror)
        s.close()
        exit(-2)
    time.sleep(0.25)

    s.close()