import socket
import struct

import select

ip = 'localhost'
port = 7777

try:
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.bind((ip, port))
    serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serverSocket.listen(10)
except socket.error as error:
    print(f"Error creating socket: {error}")
    exit(1)

print(f"Server listening on port {port}")
clients = [serverSocket]
students = []
clientUdpIp = 'localhost'

try:
    while True:
        readSockets, _, _ = select.select(clients, [], [])
        for sock in readSockets:
            if sock == serverSocket:
                clientSocket, clientAddr = serverSocket.accept()
                clients.append(clientSocket)
            else:
                ###

                availabilty = []
                learningStyle = (sock.recv(1)).decode()
                for i in range(7):
                    dayEncoded = sock.recv(4)
                    day = struct.unpack('!i', dayEncoded)[0]
                    availabilty.append(day)
                subject = (sock.recv(32)).decode()
                print(learningStyle)
                print(availabilty)
                print(subject)
                msg = "hello".encode()
                sock.send(msg)

                # clientUdpPortEncoded = sock.recv(4)
                # if not clientUdpPortEncoded:
                #     print(f"Client {sock.getpeername()} disconnected!")
                #     clients.remove(sock)
                #     sock.close()
                #     continue
                # clientUdpPort = struct.unpack('!i', clientUdpPortEncoded)[0]
                # print(f"Got the udp port {clientUdpPort} for client {clientAddr}")
                # students.append([clientUdpIp, clientUdpPort])
                # print("Sending student udp information to everyone...")
                # for student in students:
                #     studentIp = student[0]
                #     studentPort = student[1]
                #     for client in clients:
                #         if client != serverSocket:
                #             client.send(studentIp.encode())
                #             studentPortEncoded = struct.pack('!i', studentPort)
                #             client.send(studentPortEncoded)
except Exception as error:
    print(str(error))
    serverSocket.close()
    exit(1)
