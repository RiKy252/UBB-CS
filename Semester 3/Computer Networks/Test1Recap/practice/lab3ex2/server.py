import socket
import struct
import random

port = 1234
host = 'localhost'
serverNumber = random.randint(0, 10000)

clients = set()

try:
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    serverSocket.bind((host, port))
    print(f"Server listening to port {port}...")
    print(f"Server number = {serverNumber}")
    while True:
        clientData, clientAddr = serverSocket.recvfrom(4)
        clientNumber = struct.unpack('!i', clientData)[0]
        print(f"Received number {clientNumber} from {clientAddr}...")
        if clientAddr not in clients:
            clients.add(clientAddr)
        if clientNumber == serverNumber:
            serverSocket.sendto("G".encode(), clientAddr)
            for client in clients:
                if client != clientAddr:
                    serverSocket.sendto("L".encode(), client)
            break
        elif clientNumber > serverNumber:
            serverSocket.sendto("S".encode(), clientAddr)
        elif clientNumber < serverNumber:
            serverSocket.sendto("H".encode(), clientAddr)

except Exception as error:
    print(str(error))
    exit(1)
