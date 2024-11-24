import socket
import random
import struct
import select

random.seed()
start = 1
end = 2**17 - 1
my_float = random.uniform(start, end)
print("Server float: ", my_float)
winnerClient = 0
difference = 0
minim = 2 ** 17

try:
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serverSocket.settimeout(10)
    serverSocket.bind(('localhost', 1234))
except socket.error as msg:
    print(msg.strerror)
    exit(1)

try:
    clients = []
    while True:
        readSockets, _, _ = select.select([serverSocket], [], [], 10)
        if readSockets:
                clientFloat, clientAddr = serverSocket.recvfrom(4)
                if clientAddr not in clients:
                    clients.append(clientAddr)
                clientFloat = struct.unpack('!f', clientFloat)[0]
                print(f"Got {clientFloat} from {clientAddr}")
                if clientFloat == my_float:
                    message = b"You won!"
                    serverSocket.sendto(message, clientAddr)
                    for client in clients:
                        if client == serverSocket:
                            pass
                        else:
                            serverSocket.sendto(b"You lost!", client)
                            serverSocket.close()
                    print("Someone guessed, closing server...")
                    exit(1)
                else:
                    localDifference = abs(my_float - clientFloat)
                    if localDifference < minim:
                        minim = localDifference
                        winner = clientAddr
                        difference = localDifference
        else:
            try:
                print("Time's up!")
                print("Sending responses and closing connection!")
                for client in clients:
                    if client == winner:
                        winnerMessage = f"You have the best guess with an error of {difference}".encode()
                        serverSocket.sendto(winnerMessage, client)
                        print("Sent message to winner!")
                    else:
                        loserMessage = "You lost!".encode()
                        serverSocket.sendto(loserMessage, client)
                        print("Sent messages for the losers!")
                break
            except socket.error as error:
                print(str(error))
                exit(1)
except Exception as error:
    print(str(error))
    exit(1)

print("Closing server...")
serverSocket.close()
