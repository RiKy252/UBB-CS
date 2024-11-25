import socket
import select
import struct

# The client sends the complete path to a file.
# The server returns back the length of the file and its content in the case the file exists.
# When the file does not exist the server returns a length of -1 and no content.
# The client will store the content in a file with the same name as the input file with the suffix –copy appended (ex: for f.txt => f.txt-copy).

BUFFER_SIZE = 1024

host = 'localhost'
port = 1234

try:
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serverSocket.bind((host, port))
    serverSocket.listen(10)
except socket.error as error:
    print(str(error))
    exit(1)

clients = [serverSocket]
print(f"Server listening to the port {port}...")

while True:
    readSockets, _, _ = select.select(clients, [], [])
    for sock in readSockets:
        # sock == serverSocket means that a new client wants to connect, in this block we just accept it, append it to the list and if we want we send a message
        if sock == serverSocket:
            clientSocket, clientAddress = serverSocket.accept()
            clients.append(clientSocket)
            print(f"{clientAddress} connected to the server!")
            welcomeMessage = f"Welcome {clientAddress} to the server!\n".encode()
            clientSocket.send(welcomeMessage)
        # in this else block we receive data from the client
        else:
            try:
                filePath = sock.recv(BUFFER_SIZE)
                filePath = filePath.decode()
                print(f"Got {filePath} from {sock.getpeername()}!")
                try:
                    with open(filePath, 'r') as file:
                        fileContent = file.read()
                        fileLength = len(fileContent)
                    sock.send(struct.pack('!i', fileLength))
                    sock.send(fileContent.encode())
                    print(fileContent)
                    print(f"Sent the file length {fileLength} and content to {sock.getpeername()}!")
                except FileNotFoundError as error:
                    returnLength = -1
                    returnContent = b""
                    sock.send(struct.pack('!i', returnLength))
                    sock.send(returnContent)
                    print(f"File does not exist, so i sent -1 as length and no content to {sock.getpeername()}!")
                print(f"Closed connection with the socket {sock.getpeername()}!")
                clients.remove(sock)
                sock.close()

            except socket.error as error:
                print(str(error))
                exit(1)
