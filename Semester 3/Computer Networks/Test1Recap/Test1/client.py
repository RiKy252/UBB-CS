import socket
import random
import struct
import select

udpIp = 'localhost'
udpPort = random.randint(1000, 9999)
while udpPort == 7777:
    udpPort = random.randint(1000, 9999)
tcpPort = 7777
tcpIp = 'localhost'
serverAddr = (tcpIp, tcpPort)

try:
    learningStyle = input("Enter the learning style (char): ")
    if learningStyle != 'a' and learningStyle != 'v' and learningStyle != 'h':
        print("Learning style invalid!")
        exit(1)
    availability = []
    for i in range(7):
        day = int(input(f"Enter the availability for the day {i + 1} (int): "))
        if day != -1 and day != 1 and day != 2 and day != 3:
            print("Invalid day availability!")
            exit(1)
        availability.append(day)
    subject = input("Enter the subject: ")
    if len(subject) > 32:
        print("Subject length > 32")
        exit(1)
except ValueError as error:
    print(str(error))
    exit(1)

try:
    tcpSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcpSocket.connect(serverAddr)
    udpSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udpSocket.bind((udpIp, udpPort))
except socket.error as error:
    print(f"Error connecting to tcp socket, or creating the udp socket: {error}")
    exit(1)

print(f"Connected to the tcp server and formed the udp socket with IP: {udpIp} and port: {udpPort}!")
students = []

try:
    # encodedUdpPort = struct.pack('!i', udpPort)
    # tcpSocket.send(encodedUdpPort)
    # print("Sent the udp port to the server through tcp!")

    ###
    tcpSocket.send(learningStyle.encode())
    for i in range(7):
        day = struct.pack('!i', availability[i])
        tcpSocket.send(day)
    tcpSocket.send(subject.encode())

    hellomsg = (tcpSocket.recv(10)).decode()
    print(hellomsg)

    # # preference = [learningStyle, availability, subject]
    # while True:
    #     studentUdpIp = tcpSocket.recv(9).decode()
    #     if not studentUdpIp:
    #         print("Server error!")
    #         tcpSocket.close()
    #         udpSocket.close()
    #         exit(1)
    #     studentUdpPortEncoded = tcpSocket.recv(4)
    #     if not studentUdpPortEncoded:
    #         print("Server error!")
    #         tcpSocket.close()
    #         udpSocket.close()
    #         exit(1)
    #     studentUdpPort = struct.unpack('!i', studentUdpPortEncoded)[0]
    #     if studentUdpPort != udpPort and [studentUdpIp, studentUdpPort] not in students:
    #         students.append([studentUdpIp, studentUdpPort])
    #         print(f"Students: {students}")
    #     # ok = False
    #     # if students:
    #     #     while True and not ok:
    #     #         for student in students:
    #     #             if not ok:
    #     #                 studentIp = student[0]
    #     #                 studentPort = student[1]
    #     #                 udpSocket.sendto(learningStyle.encode(), (studentIp, studentPort))
    #     #                 for day in availability:
    #     #                     encodedDay = struct.pack('!i', day)
    #     #                     udpSocket.sendto(encodedDay, (studentIp, studentPort))
    #     #                 udpSocket.sendto(subject.encode(), (studentIp, studentPort))
    #     #                 potentialBuddyLearningStyle, potentialBuddyAddr = udpSocket.recvfrom(1)
    #     #                 potentialBuddyLearningStyle = potentialBuddyLearningStyle.decode()
    #     #                 potentialBuddyAvailability = []
    #     #                 for i in range(7):
    #     #                     potentialBuddyDayEncoded, potentialBuddyAddr = udpSocket.recvfrom(4)
    #     #                     potentialBuddyDay = struct.unpack('!i', potentialBuddyDayEncoded)
    #     #                     potentialBuddyAvailability.append(potentialBuddyDay)
    #     #                 potentialBuddySubject, potentialBuddyAddr = udpSocket.recvfrom(4) #####
    #     #                 potentialBuddySubject = potentialBuddySubject.decode()
    #     #                 if potentialBuddyLearningStyle == learningStyle and potentialBuddySubject == subject:
    #     #                     index = 0
    #     #                     while index < 7:
    #     #                         if potentialBuddyAvailability[index] == availability[index]:
    #     #                             ok = True
    #     #                             print(f"Match with {potentialBuddyAddr}. Closing socket")
    #     #                             udpSocket.close()
    #     #                             tcpSocket.close()
    #     #                             exit(0)


except Exception as error:
    print(str(error))
    tcpSocket.close()
    udpSocket.close()
    exit(1)
