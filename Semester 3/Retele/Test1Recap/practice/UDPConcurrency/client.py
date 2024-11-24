import socket


def main():
    server_address = ('127.0.0.1', 12345)  # Server IP and port
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    try:
        while True:
            # Get user input
            message = input("Enter message to send to the server (or 'exit' to quit): ")
            if message.lower() == 'exit':
                print("Exiting client.")
                break

            # Send the message to the server
            client_socket.sendto(message.encode(), server_address)

            # Wait for the server's response
            data, server = client_socket.recvfrom(1024)  # Buffer size is 1024 bytes
            print(f"Received response from server: {data.decode()}")

    except KeyboardInterrupt:
        print("\nClient stopped.")

    finally:
        client_socket.close()


if __name__ == "__main__":
    main()
