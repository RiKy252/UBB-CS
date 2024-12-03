import random
import math
import timeit


def generate_random_number_list(length: int) -> list:
    number_list = []
    for index in range(length):
        number_list.append(random.randint(1, 100))
    return number_list


def bubble_sort(list_to_be_sorted: list) -> list:
    is_sorted = False
    while not is_sorted:
        is_sorted = True
        for index in range(0, len(list_to_be_sorted) - 1):
            if list_to_be_sorted[index] > list_to_be_sorted[index + 1]:
                temporary_value = list_to_be_sorted[index]
                list_to_be_sorted[index] = list_to_be_sorted[index + 1]
                list_to_be_sorted[index + 1] = temporary_value
                is_sorted = False
    return list_to_be_sorted


def comb_sort(list_to_be_sorted: list) -> list:
    length = len(list_to_be_sorted)
    shrink = 1.3
    gap = length
    list_copy = list_to_be_sorted[:]
    is_sorted = False
    while not is_sorted:
        gap = math.floor(gap / shrink)
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
    return list_copy


def time_for_bubble_sort_best_case(list_to_be_timed):
    time = timeit.Timer(stmt=lambda: bubble_sort(sorted(list_to_be_timed.copy())))
    execution_time = time.timeit(number=1)
    return execution_time


def time_for_bubble_sort_average_case(list_to_be_timed):
    time = timeit.Timer(stmt=lambda: bubble_sort(list_to_be_timed.copy()))
    execution_time = time.timeit(number=1)
    return execution_time


def time_for_bubble_sort_worst_case(list_to_be_timed):
    time = timeit.Timer(stmt=lambda: bubble_sort(sorted(list_to_be_timed.copy(), reverse=True)))
    execution_time = time.timeit(number=1)
    return execution_time


def time_for_comb_sort_best_case(list_to_be_timed):
    time = timeit.Timer(stmt=lambda: comb_sort(sorted(list_to_be_timed.copy())))
    execution_time = time.timeit(number=1)
    return execution_time


def time_for_comb_sort_average_case(list_to_be_timed):
    time = timeit.Timer(stmt=lambda: comb_sort(list_to_be_timed.copy()))
    execution_time = time.timeit(number=1)
    return execution_time


def time_for_comb_sort_worst_case(list_to_be_timed):
    time = timeit.Timer(stmt=lambda: comb_sort(sorted(list_to_be_timed.copy(), reverse=True)))
    execution_time = time.timeit(number=1)
    return execution_time


while True:
    number_list_length = int(input("Insert the number of elements for the list in the first data structure: "))
    if number_list_length <= 0:
        print("Insert a valid number of elements: ")
    else:
        break
while True:
    print("")
    print("1. Bubble sort")
    print("2. Comb sort")
    print("0. Exit the program")
    print("")
    option = int(input("Choose a number from the menu: "))
    if option == 1 or option == 2 or option == 0:
        break
    else:
        print("Wrong input, try again!")
if option == 1:
    data_structures_list = []
    for index in range(0, 5):
        length_times_power_2_of_index_sized_list = generate_random_number_list(number_list_length * 2 ** index)
        data_structures_list.append(length_times_power_2_of_index_sized_list)
    while True:
        print("Best case complexity: O(n)")
        print("Worst case complexity: O(n^2)")
        print("")
        print("1. Best case configuration (elements are already sorted)")
        print("2. Average case configuration (elements are in random order)")
        print("3. Worst case configuration (elements are sorted but in reverse)")
        print("0. Exit")
        while True:
            menu_option = int(input("Choose a configuration: "))
            if menu_option == 1 or menu_option == 2 or menu_option == 3 or menu_option == 0:
                break
            else:
                print("Invalid number...")
        if menu_option == 1:
            for data_structure in data_structures_list:
                execution_time = time_for_bubble_sort_best_case(data_structure)
                print(f"Execution time: {execution_time: .6f} seconds for bubble sorting " + str(len(data_structure)) + " elements in the best case scenario")
        elif menu_option == 2:
            for data_structure in data_structures_list:
                execution_time = time_for_bubble_sort_average_case(data_structure)
                print(f"Execution time: {execution_time: .6f} seconds for bubble sorting " + str(len(data_structure)) + " elements in the average case scenario")
        elif menu_option == 3:
            # 10, 3
            for data_structure in data_structures_list:
                execution_time = time_for_bubble_sort_worst_case(data_structure)
                print(f"Execution time: {execution_time: .6f} seconds for bubble sorting " + str(len(data_structure)) + " elements in the worst case scenario")
        else:
            break
elif option == 2:

    data_structures_list = []
    for index in range(0, 5):
        length_times_power_2_of_index_sized_list = generate_random_number_list(number_list_length * 2**index)
        data_structures_list.append(length_times_power_2_of_index_sized_list)
    while True:
        print("Best case complexity: O(n*log(n))")
        print("Worst case complexity: O(n^2)")
        print("")
        print("1. Best case configuration (elements are already sorted)")
        print("2. Average case configuration (elements are in random order)")
        print("3. Worst case configuration (elements are sorted but in reverse)")
        print("0. Exit")
        while True:
            menu_option = int(input("Choose a configuration: "))
            if menu_option == 1 or menu_option == 2 or menu_option == 3 or menu_option == 0:
                break
            else:
                print("Invalid number...")
        if menu_option == 1:
            for data_structure in data_structures_list:
                execution_time = time_for_comb_sort_best_case(data_structure)
                print(f"Execution time: {execution_time: .6f} seconds for comb sorting " + str(len(data_structure)) + " elements in the best case scenario")
        elif menu_option == 2:
            for data_structure in data_structures_list:
                execution_time = time_for_comb_sort_average_case(data_structure)
                print(f"Execution time: {execution_time: .6f} seconds for comb sorting " + str(len(data_structure)) + " elements in the average case scenario")
        elif menu_option == 3:
            for data_structure in data_structures_list:
                execution_time = time_for_comb_sort_worst_case(data_structure)
                print(f"Execution time: {execution_time: .6f} seconds for comb sorting " + str(len(data_structure)) + " elements in the worst case scenario")
        else:
            break
