from multiprocessing import Process
from time import sleep


def print_numbers():
    for i in range(10):
        print(f"Number: {i}")
        sleep(2)

def print_letters():
    for letter in 'LaboratorPDB':
        print(f"Letter: {letter}")
        sleep(3) 

if __name__ == '__main__':
    p1 = Process(target=print_numbers)
    p2 = Process(target=print_letters)

    p1.start()
    p2.start()

    p1.join()
    p2.join()