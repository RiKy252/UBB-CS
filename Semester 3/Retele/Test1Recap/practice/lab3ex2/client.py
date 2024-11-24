import socket
import struct

host = 'localhost'
port = 1234
serverAddr = (host, port)
clientSocket = ""

try:
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    number = int(input("Guess: "))
    encodedNumber = struct.pack('!i', number)
    clientSocket.sendto(encodedNumber, serverAddr)
    while True:
        info, _ = clientSocket.recvfrom(1)
        if info.decode() == "H":
            newNumber = int(input("Send a larger number: "))
            newNumberEncoded = struct.pack('!i', newNumber)
            clientSocket.sendto(newNumberEncoded, serverAddr)
        elif info.decode() == "S":
            newNumber = int(input("Send a lower number: "))
            newNumberEncoded = struct.pack('!i', newNumber)
            clientSocket.sendto(newNumberEncoded, serverAddr)
        elif info.decode() == "G":
            print("You guessed my number!!!")
            break
        elif info.decode() == "L":
            print("Another client guessed the number! You lost!")
            break
except Exception as error:
    print(str(error))
    if not (clientSocket == ""):
        clientSocket.close()
    exit(1)

clientSocket.close()
