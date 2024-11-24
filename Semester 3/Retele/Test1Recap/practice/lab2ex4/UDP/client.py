import socket
import struct

port = 1234
ip = 'localhost'

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    print(f"Connectionless connected to ip: {ip}, port: {port}")
except socket.error as error:
    print(str(error))
    exit(1)

try:
    N = int(input("Enter the number of values for the array: "))
    arr = []
    for i in range(N):
        elem = float(input(f"Enter the float for the index {i + 1}: "))
        arr.append(elem)
    encodedLength = struct.pack('!i', N)
    sock.sendto(encodedLength, (ip, port))
    print(f"Sent the length {N} to the server!")
    for elem in arr:
        encodedElem = struct.pack('!f', elem)
        sock.sendto(encodedElem, (ip, port))
    # encodedArray = struct.pack(f'!{N}f', *arr)
    # sock.sendto(encodedArray, (ip, port))
    print("Sent the float array to the server!")
    print("Waiting for the server to send results...")
    finalArrayLengthEncoded, _ = sock.recvfrom(4)
    finalArrayLength = struct.unpack('!i', finalArrayLengthEncoded)[0]
    globalArray = []
    for _ in range(finalArrayLength):
        floatEncoded, _ = sock.recvfrom(4)
        if not floatEncoded:
            print("Server disconnected sending array!")
            sock.close()
            continue
        floatNumber = struct.unpack('!f', floatEncoded)[0]
        globalArray.append(floatNumber)
    print(f"Array length: {finalArrayLength}: {globalArray}")
    print("Done")
    sock.close()
except Exception as error:
    print(str(error))
    sock.close()
    exit(1)
