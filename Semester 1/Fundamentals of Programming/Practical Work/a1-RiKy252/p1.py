# Problem 1

def is_prime(x):
    d = 2
    cnt = 1
    while x > 1:
        p = 0
        while x % d == 0:
            p += 1
            x /= d
        cnt *= (p + 1)
        d += 1
        if d * d > x:
            d = x
    return cnt == 2


def next_prime(num):
    cpy = num + 1
    while True:
        if is_prime(cpy):
            return cpy
        cpy += 1


n = int(input("Enter a natural number: "))
res = next_prime(n)
print("The first prime number larger than " + str(n) + " is: " + str(res))
