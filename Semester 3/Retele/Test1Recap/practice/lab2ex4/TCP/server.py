import socket
import struct
import select

port = 1234
ip = 'localhost'

try:
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serverSocket.bind((ip, port))
    serverSocket.listen(10)
except socket.error as error:
    print(str(error))
    exit(1)

clients = [serverSocket]
print(f"Server listening on port {port}")
globalArray = []

try:
    while True:
        readSockets, _, _ = select.select(clients, [], [])
        for sock in readSockets:
            if sock == serverSocket:
                clientSocket, clientAddr = serverSocket.accept()
                welcomeMessage = f"Welcome {clientAddr} to the server!"
                clientSocket.send(welcomeMessage.encode())
                clients.append(clientSocket)
            else:
                arrayLengthEncoded = sock.recv(4)
                if not arrayLengthEncoded:
                    print(f"Client {sock.getpeername()} disconnected sending length!")
                    clients.remove(sock)
                    sock.close()
                    continue
                arrayLength = struct.unpack('!i', arrayLengthEncoded)[0]
                if arrayLength == 0:
                    # Send to all clients the final sorted array and its length
                    globalArrayLength = len(globalArray)
                    for client in clients:
                        if client != serverSocket:
                            globalArrayLengthEncoded = struct.pack('!i', globalArrayLength)
                            client.send(globalArrayLengthEncoded)
                            globalArrayEncoded = struct.pack(f'!{globalArrayLength}f', *globalArray)
                            client.send(globalArrayEncoded)
                    print("Sent to clients the results! Closing server...")
                    serverSocket.close()
                    exit(0)
                else:
                    print(f"Got the array length {arrayLength} from the client {sock.getpeername()}!")
                    array = []
                    for _ in range(arrayLength):
                        floatEncoded = sock.recv(4)
                        if not floatEncoded:
                            print(f"Client {sock.getpeername()} disconnected sending array!")
                            clients.remove(sock)
                            sock.close()
                            continue
                        floatNumber = struct.unpack('!f', floatEncoded)[0]
                        array.append(floatNumber)
                    print(f"Got the float array from the client {sock.getpeername()}: {array}")
                    for i in range(arrayLength):
                        globalArray.append(array[i])
                    globalArray.sort()
                    print(f"Sorted array from all clients: {globalArray}")
except Exception as error:
    print(str(error))
    serverSocket.close()
    exit(1)
