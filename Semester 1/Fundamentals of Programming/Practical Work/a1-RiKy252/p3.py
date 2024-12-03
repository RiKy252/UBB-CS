# Problem 15

def sum_of_divisors(n):
    d = 1
    sum = 0
    while d * d <= n:
        if n % d == 0:
            sum += d
            sum += (n / d)
        if d * d == n:
            sum -= d
        d += 1
    return sum


def perfect_number(n):
    if n == 0 or n == 1 or n == 2 or n == 3:
        return False
    return sum_of_divisors(n) - n == n


def prev_perfect_number(n):
    tmp = n - 1
    while perfect_number(tmp) == False and tmp != 1:
        tmp -= 1
    return tmp


given_number = int(input("Enter a natural number: "))
result = prev_perfect_number(given_number)
if result == 1:
    print("There does not exist a perfect number smaller than " + str(given_number) + "...")
else:
    print("The largest perfect number smaller than " + str(given_number) + " is: " + str(result))
