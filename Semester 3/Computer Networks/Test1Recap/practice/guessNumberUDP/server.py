import random
import socket
import struct

# Create UDP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind(("localhost", 1234))

print("Server is ready to serve multiple clients...")

serverNumber = random.randint(1, 100)
clients = []

try:
    while True:
        # Receive a message from a client
        msg, client_addr = server_socket.recvfrom(1024)
        if msg.decode() == "ok":
            clients.remove(client_addr)
        if client_addr not in clients:
            clients.append(client_addr)
            # Initialize the game for a new client
            welcome_msg = ("Welcome to Guess the Number! Guess a number, and I'll tell you if it's too high, "
                            "too low, or correct. Have fun!")
            server_socket.sendto(welcome_msg.encode(), client_addr)
            print(f"New client connected: {client_addr}, target number is {serverNumber}")
            continue
        # Unpack and process the guessed number
        guessed_number = struct.unpack("!I", msg)[0]
        target_number = serverNumber

        print(f"Client {client_addr} guessed {guessed_number}, target is {target_number}")

        if guessed_number < target_number:
            server_socket.sendto(b"H", client_addr)  # Hint: Higher
        elif guessed_number > target_number:
            server_socket.sendto(b"L", client_addr)  # Hint: Lower
        else:
            server_socket.sendto(b"W", client_addr)  # Win message
            winning_msg = "Congratulations! You guessed the number!"
            loser_msg = "Sorry! Someone got the guessed number before you! Game over!"
            server_socket.sendto(winning_msg.encode(), client_addr)
            print(f"Client {client_addr} won with the number {guessed_number}.")
            clients.remove(client_addr)
            for client in clients:
                server_socket.sendto(b"LOST", client)
                server_socket.sendto(loser_msg.encode(), client)
except Exception as e:
    print(f"Error: {e}")
finally:
    server_socket.close()
