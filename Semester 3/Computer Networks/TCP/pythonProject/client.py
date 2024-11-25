__author__ = 'dadi'

# import socket for all socket related primitives
import socket
# we need struct in order to be able to pack data in
# a stream of bytes so that we can actually send
# an integer as a binary four byte sequence - instead
# of a string
import struct


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# The obscure struct_addr is elegantly replaced by
# a simple pair - very convenient. Replace the IP Address with
# the one of your server
s.connect(('localhost', 1234))

with open("fisier.txt", "rb") as file:
    while True:
        bytesRead = file.read(2048)
        if not bytesRead:
            break
        s.sendall(bytesRead)

print("File sent successfully!")
s.shutdown(socket.SHUT_WR)
c = s.recv(4)

# unpack the content read from the network into a short int
# and convert from network representation back to host
c = struct.unpack('!I', c)
print('file size = ' + c[0].__format__('d'))

s.close()
