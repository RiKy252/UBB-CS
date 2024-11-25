import socket


def udp_server(port):
    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Bind the socket to all interfaces
    server_address = ('0.0.0.0', port)
    sock.bind(server_address)

    print(f"UDP server listening on port {port}")

    while True:
        # Wait for a message from a client
        data, address = sock.recvfrom(1024)
        print(f"Received {len(data)} bytes from {address}")
        print(data.decode())

        # Send a confirmation response
        if data:
            response = "Got your message\n"
            sent = sock.sendto(response.encode(), address)
            print(f"Sent {sent} bytes back to {address}")


if __name__ == "__main__":
    port = int(input("Enter the port number for the server: "))
    udp_server(port)
