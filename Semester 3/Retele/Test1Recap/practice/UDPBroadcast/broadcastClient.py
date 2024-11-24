import socket


def udp_client(server_ip, port):
    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # Broadcast address = ipAddr or !subnetMask -> 10.131.255.255
    broadcastAddr = ('10.131.255.255', port)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    message = input("Please enter the message: ")

    try:
        # Send data
        sent = sock.sendto(message.encode(), broadcastAddr)
        print(f"Sent {sent} bytes to {broadcastAddr}")

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
