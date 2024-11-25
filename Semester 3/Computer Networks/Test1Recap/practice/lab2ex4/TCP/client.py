import socket
import struct

port = 1234
ip = 'localhost'

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ip, port))
    print("Connected!")
    message = sock.recv(1024)
    print(message.decode())
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
    encodedArray = struct.pack(f'!{N}f', *arr)
    sock.send(encodedLength)
    print(f"Sent the length {N} to the server!")
    sock.send(encodedArray)
    print("Sent the float array to the server!")
    print("Waiting for the server to send results...")
    finalArrayLengthEncoded = sock.recv(4)
    finalArrayLength = struct.unpack('!i', finalArrayLengthEncoded)[0]
    globalArray = []
    for _ in range(finalArrayLength):
        floatEncoded = sock.recv(4)
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
