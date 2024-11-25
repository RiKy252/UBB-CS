import socket
import struct

port = 1234
ip = '0.0.0.0'
broadcastAddr = ('10.131.255.255', port)

try:
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    serverSocket.bind((ip, port))
except socket.error as error:
    print(f"Socket error: {error}")
    exit(1)

print(f"Server listening on port {port}")
globalArray = []

try:
    while True:
        # Receive array data from a client
        data, clientAddr = serverSocket.recvfrom(4096)
        if not data:
            continue

        # Decode array length and data
        arrayLength = struct.unpack('!i', data[:4])[0]
        array = struct.unpack(f'!{arrayLength}f', data[4:])
        print(f"Received array from {clientAddr}: {array}")

        # Update the global array
        globalArray.extend(array)
        globalArray.sort()
        print(f"Sorted global array: {globalArray}")

        # Send the sorted array via broadcast
        globalArrayLength = len(globalArray)
        globalArrayLengthEncoded = struct.pack('!i', globalArrayLength)
        globalArrayEncoded = struct.pack(f'!{globalArrayLength}f', *globalArray)
        broadcastMessage = globalArrayLengthEncoded + globalArrayEncoded

        # Broadcasting to the subnet
        serverSocket.sendto(broadcastMessage, ('<broadcast>', port))
        print("Broadcast sorted array to all clients!")
except Exception as error:
    print(f"Error: {error}")
    serverSocket.close()
    exit(1)
