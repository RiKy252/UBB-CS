import struct
import socket

host = 'localhost'
port = 1234

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
except socket.error:
    print("Error creating and connecting to the host server")
    exit(1)

print(f"Successfully connect to the port {port}")

try:
    userString = input("Enter the string that will be sent to the server to compute the space count: ")
    s.sendall(userString.encode())
    print("String sent!")
    s.shutdown(socket.SHUT_WR)
    spaceCount = s.recv(4)
    spaceCount = struct.unpack('!i', spaceCount)[0]
    print(f"Space count = {spaceCount}! Closing connection...")
    s.close()
except socket.error as error:
    print(str(error))
    exit(1)
