# Problem 8

def fibonacci(n):
    if n == 0 or n == 1:
        return 1
    return fibonacci(n-1) + fibonacci(n-2)


def next_fibonacci_index(number):
    idx = 2
    while fibonacci(idx) <= number:
        idx += 1
    return idx


num = int(input("Enter a natural number greater than 2: "))
m = fibonacci(next_fibonacci_index(num))
print("The smallest number from the Fibonacci sequence larger than " + str(num) + " is: " + str(m))
