import threading

# Shared variable
shared_var = 'A'
def thread_1():
    global shared_var
    temp = shared_var
    if temp == 'A':
        temp = 'C'
        # Context switch happens here, and thread_2 changes shared_var to 'B'
        print(f"Thread 1: {temp}")
    else:
        print(f"Thread 1: {temp} - skipped")
    shared_var = temp

def thread_2():
    global shared_var
    temp = shared_var
    temp = 'B'
    # Context switch happens here, and thread_1 changes shared_var to 'C'
    print(f"Thread 2: {temp}")
    shared_var = temp

# Run 200 times
num_b = 0
num_c = 0

lock = threading.Lock()
for _ in range(2000):
    t1 = threading.Thread(target=thread_1)
    t2 = threading.Thread(target=thread_2)

    t1.start()
    t2.start()

    # t1.join()
    # t2.join()

    if shared_var == 'B':
        num_b += 1
    elif shared_var == 'C':
        num_c += 1

print(f"Number of B: {num_b}")
print(f"Number of C: {num_c}")


### Mutex Preventive Techniques:

## Locks

# import threading

#     # critical section

## Semaphores: A generalization of mutexes, allowing more than one thread to enter the critical section.

# semaphore = threading.Semaphore(2)
# with semaphore:
#     # critical section

## Monitors: An object-oriented approach to mutual exclusion, encapsulating the shared resource and its mutex.


# class Monitor:
#     def __init__(self):
#         self.lock = threading.Lock()

#     def method(self):
#         with self.lock:
#             # critical section
# Cnditional Object https://docs.python.org/3/library/threading.html#condition-objects
# condition = threading.Condition()
# with condition:
#     # critical section
#     condition.notify_all()
    
# Barriers: https://docs.python.org/3/library/threading.html#barrier-objects