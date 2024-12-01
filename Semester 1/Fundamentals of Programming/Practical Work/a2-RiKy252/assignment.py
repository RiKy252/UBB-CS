import random
from math import floor


def bubble_sort(list_to_be_sorted: list, step: int) -> list:
    is_sorted = False
    step_counter = 0
    while not is_sorted:
        is_sorted = True
        for index in range(0, len(list_to_be_sorted) - 1):
            if list_to_be_sorted[index] > list_to_be_sorted[index + 1]:
                temporary_value = list_to_be_sorted[index]
                list_to_be_sorted[index] = list_to_be_sorted[index + 1]
                list_to_be_sorted[index + 1] = temporary_value
                is_sorted = False
                step_counter += 1
                if step_counter % step == 0:
                    print("The list after step no. " + str(step_counter) + " is " + str(list_to_be_sorted))
    return list_to_be_sorted


def comb_sort(list_to_be_sorted: list, step: int) -> list:
    step_counter = 0
    length = len(list_to_be_sorted)
    shrink = 1.3
    gap = length
    list_copy = list_to_be_sorted
    is_sorted = False
    while not is_sorted:
        gap = floor(gap / shrink)
        if gap <= 1:
            is_sorted = True
            gap = 1
        for index in range(length - gap):
            gap_index = gap + index
            if list_copy[index] > list_copy[gap_index]:
                aux = list_copy[index]
                list_copy[index] = list_copy[gap_index]
                list_copy[gap_index] = aux
                is_sorted = False
                step_counter += 1
                if step_counter % step == 0:
                    print("The list after step no. " + str(step_counter) + " is " + str(list_copy))
    return list_copy


while True:
    print("")
    print("1. Generate a list of n random natural numbers.")
    print("2. Sort the list using bubble sort")
    print("3. Sort the list using comb sort")
    print("0. Exit the program")
    print("")
    option = int(input("Choose a number from the menu: "))
    if option == 0:
        break
    elif option == 1:
        numberCount = int(input("Choose the number (n) for how many random numbers the program will generate: "))
        randomNumbersList = []
        for i in range(numberCount):
            randomNumber = random.randint(0, 100)
            randomNumbersList.append(randomNumber)
        print("The generated list is: " + str(randomNumbersList))
    elif option == 2:
        if not randomNumbersList:
            print("There is no list generated so that we can use bubble sort...")
            print("")
        else:
            step_user = int(input("Enter the value for the step parameter: "))
            sorted_list = bubble_sort(randomNumbersList.copy(), step_user)
            print("")
            print("The final sorted list using the bubble sort method looks like this: " + str(sorted_list))
    elif option == 3:
        if not randomNumbersList:
            print("There is no list generated so that we can use comb sort...")
            print("")
        else:
            step_user = int(input("Enter the value for the step parameter: "))
            sorted_list = comb_sort(randomNumbersList.copy(), step_user)
            print("")
            print("The final sorted list using the comb sort method looks like this: " + str(sorted_list))
    else:
        print("Wrong input, try again!")
