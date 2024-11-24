import socket
import sys

BUFFER_SIZE = 1024

def main():
    port = 1234
    server_ip = "localhost"

    # Create UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    print(f"Connected to chat server at {server_ip}:{port}")

    while True:
        # Get input from user and send to the server
        message = input("You: ")
        if message.lower() == "quit":
            print("Exiting chat...")
            break

        # Send message to the server
        sock.sendto(message.encode(), (server_ip, port))

        # Receive message from the server
        data, _ = sock.recvfrom(BUFFER_SIZE)
        print(f"Server: {data.decode()}")

    sock.close()

if __name__ == "__main__":
    main()
