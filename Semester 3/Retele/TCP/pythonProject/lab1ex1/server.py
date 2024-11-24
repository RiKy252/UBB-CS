import socket
import struct

host = 'localhost'
port = 1234
MIN_INT, MAX_INT = -2147483648, 2147483647

serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket.bind((host, port))
serverSocket.listen(5)
print(f"Server listening on port: {port}")

while True:
    clientSocket, clientAddress = serverSocket.accept()
    print(f"{clientAddress} connected to the server!")
    arrSum = 0
    data = clientSocket.recv(4)
    if not data:
        print("Could not receive the array size from the client! Closing connection...")
        exit(1)
    length = struct.unpack('!i', data)[0]
    for _ in range(length):
        clientData = clientSocket.recv(4)
        if not clientData:
            break
        else:
            number = struct.unpack('!i', clientData)[0]
            arrSum += number
    if arrSum < MIN_INT or arrSum > MAX_INT:
        raise ValueError("The sum does not fit an integer!")
    print(f"Got the array from the client! The sum is {arrSum}, sending it to the client...")
    clientSocket.sendall(struct.pack('!i', arrSum))
    clientSocket.close()
    print(f"Connection closed for the client {clientAddress}")

