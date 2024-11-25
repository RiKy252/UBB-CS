import socket
import struct

host = 'localhost'
port = 1234

MAX_ARRAY_SIZE = 1000
MIN_INT, MAX_INT = -2147483648, 2147483647

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
except socket.error as e:
    print(str(e))
    exit(1)

try:
    n = int(input("Enter the number of elements that the array will hold: "))
    if n <= 0 or n > MAX_ARRAY_SIZE:
        raise ValueError(f"Array size must be between 1 and {MAX_ARRAY_SIZE}")
    arr = []
    for i in range(n):
        try:
            x = int(input(f"Enter the value for the element {i + 1}: "))
            if x < MIN_INT or x > MAX_INT:
                raise ValueError(f"The integer must be between {MIN_INT} and {MAX_INT}!")
        except ValueError as e:
            print(str(e))
            exit(1)
        arr.append(x)
except ValueError as e:
    print(str(e))
    exit(1)
try:
    content = struct.pack('!i', n)
    for number in arr:
        content += struct.pack('!i', number)
    s.sendall(content)
except struct.error as e:
    print(str(e))
    exit(1)
print("Array sent successfully!")
s.shutdown(socket.SHUT_WR)
try:
    serverSum = s.recv(4)
    serverSum = struct.unpack('!i', serverSum)[0]
    print(f"Array sum is: {serverSum}")
    s.close()
except socket.error as e:
    print(str(e))
    exit(1)
