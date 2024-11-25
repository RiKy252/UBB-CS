import socket, select, sys


def main():
    port = 1234
    server_ip = "localhost"

    # Create socket and connect to server
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((server_ip, port))
    print(f"Connected to chat server at {server_ip}:{port}")

    socketList = [sock]

    while True:
        read_sockets, _, _ = select.select(socketList, [], [])

        for s in read_sockets:
            if s == sock:
                data = s.recv(1024)
                if not data:
                    print("Server closed the connection.")
                    sys.exit()
                else:
                    print(data.decode())
            else:
                msg = input()
                sock.send(msg.encode())


if __name__ == "__main__":
    main()
