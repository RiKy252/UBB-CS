import socket
import select


def main():
    # Create a UDP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind(('0.0.0.0', 12345))  # Bind to all interfaces on port 12345
    print("UDP server is running...")

    # List of sockets to monitor (just one in this case)
    sockets_list = [server_socket]

    while True:
        # Use select to wait for incoming data
        readable, _, _ = select.select(sockets_list, [], [])
        for sock in readable:
            if sock == server_socket:
                # Receive data from the client
                data, client_address = server_socket.recvfrom(1024)  # Buffer size is 1024 bytes
                print(f"Received message from {client_address}: {data.decode()}")

                # Send a response to the client
                response = f"Echo: {data.decode()}"
                server_socket.sendto(response.encode(), client_address)


if __name__ == "__main__":
    main()
