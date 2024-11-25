__author__ = 'dadi'

# Import socket for network communication
import socket
import struct

# Define IP and port for the server to listen on
HOST = 'localhost'  # Listen on all network interfaces
PORT = 1234  # Same port as the client

# Create the server socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))

# Enable the server to accept connections, up to 5 clients in the queue
server_socket.listen(5)
print("Server listening on port", PORT)

while True:
    # Accept a client connection
    client_socket, client_address = server_socket.accept()
    print("Connected by", client_address)

    # Prepare to receive the file data
    file_data = b""
    # Receive data in chunks
    while True:
        data = client_socket.recv(2048)
        if not data:
            break
        file_data += data  # Append the received data to file_data

    print("Saved the data from the file!")

    # Save the received data to a file
    with open("received_file.txt", "wb") as file:
        file.write(file_data)

    # Calculate the size of the received file data
    file_size = len(file_data)
    print("Received file size:", file_size, "bytes")

    # Send back the file size to the client as a 4-byte integer
    client_socket.sendall(struct.pack('!I', file_size))
    print("Sent file size back to client.")

    # Close the client connection
    client_socket.close()
    print("Connection closed.")

# Close the server socket when done (not reached in this loop)
server_socket.close()
