import socket
import struct

port = 1234

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    broadcastAddr = ('10.131.255.255', port)
    sock.bind(('', port))  # Bind to all available interfaces
    print(f"Listening for broadcasts on port {port}")
except socket.error as error:
    print(f"Socket error: {error}")
    exit(1)

try:
    # Send array data to the server
    N = int(input("Enter the number of values for the array: "))
    arr = [float(input(f"Enter float for index {i + 1}: ")) for i in range(N)]
    encodedData = struct.pack('!i', N) + struct.pack(f'!{N}f', *arr)
    serverAddress = ('localhost', port)
    sock.sendto(encodedData, serverAddress)
    print(f"Sent array to server: {arr}")

    # Wait for broadcast message
    print("Waiting for sorted array broadcast...")
    data, _ = sock.recvfrom(4096)
    sortedArrayLength = struct.unpack('!i', data[:4])[0]
    sortedArray = struct.unpack(f'!{sortedArrayLength}f', data[4:])
    print(f"Received sorted array: {sortedArray}")
except Exception as error:
    print(f"Error: {error}")
finally:
    sock.close()
