import socket

BUFFER_SIZE = 256


def broadcast_message(message, sender_address, clients, server_socket):
    """Send message to all clients except the sender and the server socket."""
    for client_address in clients:
        if client_address != sender_address:
            try:
                server_socket.sendto(message, client_address)
            except Exception as e:
                print(f"Error sending message to {client_address}: {e}")
                clients.remove(client_address)


def main(port):
    # Initialize server socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind(('localhost', port))

    clients = set()  # Using a set to track connected clients

    print(f"Server listening on port {port}")

    while True:
        # Receive data from a client
        message, client_address = server_socket.recvfrom(BUFFER_SIZE)
        if client_address not in clients:
            clients.add(client_address)
            print(f"New client connected from {client_address}")
            welcome_message = f"Welcome to the chat, {client_address}!\n".encode()
            server_socket.sendto(welcome_message, client_address)

        # Broadcast message from the client to all other clients
        if message:
            broadcast_message(message, client_address, clients, server_socket)
        else:
            print(f"Client {client_address} disconnected.")
            clients.remove(client_address)


if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        print("Usage: python server.py <port>")
    else:
        main(int(sys.argv[1]))
