import socket
import struct

BUFFER_SIZE = 512

port = 1234
serverAddr = ('localhost', port)

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except socket.error as error:
    print(str(error))
    exit(1)

try:
    clientFloat = float(input("Enter the guessing float: "))
    encodedFloat = struct.pack('!f', clientFloat)
    sock.sendto(encodedFloat, serverAddr)
    print(f"Sent {clientFloat} to the server address ({serverAddr}), waiting for a response...")
    message, _ = sock.recvfrom(BUFFER_SIZE)
    print(f"Received message: {message.decode()}")
    sock.close()
    exit(0)
except (ValueError, socket.error) as error:
    print(str(error))
    sock.close()
    exit(1)
