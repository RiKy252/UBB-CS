import socket

def udp_client(server_ip, port):
    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    server_address = (server_ip, port)
    message = input("Please enter the message: ")

    try:
        # Send data
        sent = sock.sendto(message.encode(), server_address)
        print(f"Sent {sent} bytes to {server_address}")

        # Receive response
        data, server = sock.recvfrom(1024)
        print("Got an ack:", data.decode())

    finally:
        print("Closing socket")
        sock.close()


if __name__ == "__main__":
    server_ip = 'localhost'
    port = 1234
    udp_client(server_ip, port)
