import socket
import struct
import select

port = 1234
ip = 'localhost'

try:
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    serverSocket.bind((ip, port))
except socket.error as error:
    print(str(error))
    exit(1)

# only one socket to monitor in case of UDP
socketsList = [serverSocket]
print(f"Server listening on port {port}")
globalArray = []
clients = []

try:
    while True:
        # using select in udp to wait for data:
        readSockets, _, _ = select.select(socketsList, [], [])
        for sock in readSockets:
            if sock == serverSocket:
                arrayLengthEncoded, clientAddr = serverSocket.recvfrom(4)
                if clientAddr not in clients:
                    clients.append(clientAddr)
                if not arrayLengthEncoded:
                    print(f"Client {clientAddr} disconnected sending length!")
                    clients.remove(clientAddr)
                    continue
                arrayLength = struct.unpack('!i', arrayLengthEncoded)[0]
                if arrayLength == 0:
                    # Send to all clients the final sorted array and its length
                    globalArrayLength = len(globalArray)
                    globalArrayLengthEncoded = struct.pack('!i', globalArrayLength)
                    for client in clients:
                        serverSocket.sendto(globalArrayLengthEncoded, client)
                        for i in range(globalArrayLength):
                            chunk = struct.pack('!f', globalArray[i])
                            serverSocket.sendto(chunk, client)
                        # globalArrayEncoded = struct.pack(f'!{globalArrayLength}f', *globalArray)
                        # serverSocket.sendto(globalArrayEncoded, client)
                    print("Sent to clients the results! Closing server...")
                    serverSocket.close()
                    exit(0)
                else:
                    print(f"Got the array length {arrayLength} from the client {clientAddr}!")
                    array = []
                    for _ in range(arrayLength):
                        floatEncoded, _ = serverSocket.recvfrom(4)
                        if not floatEncoded:
                            print(f"Client {clientAddr} disconnected sending array!")
                            clients.remove(clientAddr)
                            continue
                        floatNumber = struct.unpack('!f', floatEncoded)[0]
                        array.append(floatNumber)
                    print(f"Got the float array from the client {clientAddr}: {array}")
                    for i in range(arrayLength):
                        globalArray.append(array[i])
                    globalArray.sort()
                    print(f"Sorted array from all clients: {globalArray}")
except Exception as error:
    print(str(error))
    serverSocket.close()
    exit(1)
