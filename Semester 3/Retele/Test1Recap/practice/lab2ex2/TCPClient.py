import socket
import struct

BUFFER_SIZE = 1024

host = 'localhost'
port = 1234

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
except socket.error as error:
    print(str(error))
    exit(1)


try:
    welcomeMessage = s.recv(BUFFER_SIZE).decode()
    print(welcomeMessage)
    fileName = input("Enter the entire file path for a file: ")
    s.send(fileName.encode())
    print("File name sent to the server!")
    # s.shutdown(socket.SHUT_WR)
    fileLength = s.recv(4)
    fileLength = struct.unpack('!i', fileLength)[0]
    fileContent = s.recv(BUFFER_SIZE).decode()
    print(f"Got the file length {fileLength} and content from the server!")
    print("Creating copy of the file...")
    copyFile = f"{fileName}-copy"
    with open(copyFile, 'w') as file:
        file.write(fileContent)
    print("Done!")
except socket.error as error:
    print(str(error))
    exit(1)
