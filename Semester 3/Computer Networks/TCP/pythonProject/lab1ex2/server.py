import struct
import socket

host = 'localhost'
port = 1234

try:
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serverSocket.bind((host, port))
    serverSocket.listen(5)
except socket.error:
    print("Error creating or binding the socket!")
    exit(1)

print(f"Server listening on port {port}...")

while True:
    try:
        clientSocket, clientAddress = serverSocket.accept()
        print(f"{clientAddress} connected to the server!")
        count = 0
        clientString = clientSocket.recv(1024)
        if not clientString:
            print("Did not receive anything from the client!")
            exit(1)
        print("Received the string from the client!")
        clientString = clientString.decode()
        for char in clientString:
            if char == ' ':
                count += 1
        print(f"Client spaces count = {count}, sending it now to the client...")
        clientSocket.sendall(struct.pack('!i', count))
        clientSocket.close()
    except socket.error as error:
        print(str(error))
        exit(1)
