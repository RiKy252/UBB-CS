import socket
import select

BUFFER_SIZE = 256


def broadcast_message(message, sender_socket, clients, server_socket):
    """Send message to all clients except the sender and the server socket."""
    for client_socket in clients:
        if client_socket != sender_socket and client_socket != server_socket:
            try:
                client_socket.send(message)
            except Exception as e:
                print(f"Error sending message to client: {e}")
                client_socket.close()
                clients.remove(client_socket)


def main():
    port = 1234
    # Initialize server socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind(("0.0.0.0", port))
    server_socket.listen(10)

    clients = [server_socket]

    print(f"Server listening on port {port}")

    while True:
        # Use select to handle multiple clients
        read_sockets, _, _ = select.select(clients, [], [])

        for notified_socket in read_sockets:
            # New connection
            if notified_socket == server_socket:
                client_socket, client_address = server_socket.accept()
                clients.append(client_socket)
                print(f"New connection from {client_address}")
                welcome_message = f"Welcome {client_address} to the chat!\n".encode()
                client_socket.send(welcome_message)

            # Handle message from a client
            else:
                try:
                    message = notified_socket.recv(BUFFER_SIZE)
                    if message:
                        broadcast_message(message, notified_socket, clients, server_socket)
                    else:
                        print(f"Client disconnected: {notified_socket.getpeername()}")
                        clients.remove(notified_socket)
                        notified_socket.close()
                except Exception as e:
                    print(f"Error: {e}")
                    clients.remove(notified_socket)
                    notified_socket.close()

    server_socket.close()


if __name__ == "__main__":
    main()
