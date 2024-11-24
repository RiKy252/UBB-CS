import socket
import struct


s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print("Client connected..")

guessed = False

try:
    s.sendto(b"Hello server!", ("localhost", 1234))

    wellcome_msg, addr = s.recvfrom(1024)
    print(f"{wellcome_msg.decode()} from : {addr}")

    while not guessed:
        number = int(input("Enter a number: "))
        try:
            print("Sending number..")
            s.sendto(struct.pack("!I", number), addr)
            answer, addr = s.recvfrom(1024)
            answer = answer.decode()

            if answer == "H":
                print("Enter a higher number!")
            elif answer == "L":
                print("Enter a lower number!")
            elif answer == "W":
                winning_msg, addr = s.recvfrom(1024)
                print(winning_msg.decode())
                guessed = True
            elif answer == "LOST":
                lost_msg, _ = s.recvfrom(1024)
                print(lost_msg.decode())
                s.sendto(b"ok", addr)
                break
        except Exception as e:
            print(e)
except Exception as e:
    print(e)
finally:
    s.close()
