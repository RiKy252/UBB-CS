import socket
import sys


def error(msg):
    print(f"Error: {msg}")
    sys.exit(1)


def main():
    # windows: server_ip = '172.30.249.47'
    server_ip = '192.168.60.42'
    port = 1234

    # Create UDP socket
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    except socket.error as e:
        error(f"Socket creation failed: {e}")

    server_address = (server_ip, port)

    # Message prompt
    message = input("Please enter the message: ")

    try:
        # Send message
        sent = sock.sendto(message.encode(), server_address)

        # Receive response
        data, server = sock.recvfrom(256)
        print("Got an ack:", data.decode())

    except socket.error as e:
        error(f"Communication failed: {e}")

    finally:
        sock.close()


if __name__ == "__main__":
    main()
