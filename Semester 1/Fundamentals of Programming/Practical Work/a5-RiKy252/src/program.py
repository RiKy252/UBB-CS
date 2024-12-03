from random import randint
from math import sqrt

#
# Write the implementation for A5 in this file
#

# 
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


def create_complex_number_list_representation(real_part: int, imaginary_part: int) -> list:
    return [real_part, imaginary_part]


def get_imaginary_part_list(complex_number: list):
    return complex_number[1]


def get_real_part_list(complex_number: list):
    return complex_number[0]


def list_to_string(complex_number: list) -> str:
    real_part = get_real_part_list(complex_number)
    imaginary_part = get_imaginary_part_list(complex_number)
    if imaginary_part < 0:
        return str(real_part) + " - " + str(imaginary_part)[1:] + "i"
    elif imaginary_part == 0:
        return str(real_part)
    return str(real_part) + " + " + str(imaginary_part) + "i"


def generate_random_complex_numbers_list(number_of_generations: int) -> list:
    result = []

    while number_of_generations > 0:
        real_number = randint(-100, 100)
        imaginary_number = randint(-100, 100)
        result.append(create_complex_number_list_representation(real_number, imaginary_number))
        number_of_generations -= 1
    return result


#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


def create_complex_number_dictionary_representation(real: int, imaginary: int) -> dict:
    return {"real_part": real, "imaginary_part": imaginary}


def get_imaginary_part_dictionary(complex_number: dict):
    return complex_number["imaginary_part"]


def get_real_part_dictionary(complex_number: dict):
    return complex_number["real_part"]


def dictionary_to_string(complex_number: dict) -> str:
    real_part = get_real_part_dictionary(complex_number)
    imaginary_part = get_imaginary_part_dictionary(complex_number)
    if imaginary_part < 0:
        return str(real_part) + " - " + str(imaginary_part)[1:] + "i"
    elif imaginary_part == 0:
        return str(real_part)
    return str(real_part) + " + " + str(imaginary_part) + "i"


def generate_random_complex_numbers_dictionary(number_of_generations: int) -> list:
    result = []

    while number_of_generations > 0:
        real_number = randint(-100, 100)
        imaginary_number = randint(-100, 100)
        result.append(create_complex_number_dictionary_representation(real_number, imaginary_number))
        number_of_generations -= 1
    return result


#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values

# Length and elements of the longest subarray of numbers that contain at most 3 distinct values


def get_complex_number_modulus(complex_number):
    real_part = get_real_part_list(complex_number)
    # real_part = get_real_part_dictionary(complex_number)
    imaginary_part = get_imaginary_part_list(complex_number)
    # imaginary_part = get_imaginary_part_dictionary(complex_number)
    real_part_squared = real_part ** 2
    imaginary_part_squared = imaginary_part ** 2
    complex_number_modulus = sqrt(real_part_squared + imaginary_part_squared)
    return complex_number_modulus


def replace_complex_numbers_with_their_modulus(complex_numbers: list):
    complex_numbers_modulus = []
    for complex_number in complex_numbers:
        complex_numbers_modulus.append(get_complex_number_modulus(complex_number))
    return complex_numbers_modulus


def replace_modulus_with_their_corresponding_complex_numbers(modulus_of_complex_numbers: list, complex_numbers: list):
    modulus_index = 0
    resulted_list = []
    for complex_number in complex_numbers:
        if modulus_index == len(modulus_of_complex_numbers):
            break
        if get_complex_number_modulus(complex_number) == modulus_of_complex_numbers[modulus_index]:
            resulted_list.append(complex_number)
            modulus_index += 1
    return resulted_list


def get_longest_subarray_of_with_at_most_3_distinct_values_naive(complex_numbers: list):
    """
    This function finds the longest subarray of complex numbers with at most 3 distinct values
    :param complex_numbers: the list of complex numbers
    :return: a list representing the longest subarray with at most 3 distinct values
    """
    longest_subarray_of_complex_numbers_with_at_most_3_distinct_values = []
    length_of_complex_numbers_list = len(complex_numbers)
    for starting_index in range(length_of_complex_numbers_list):
        distinct_values = [complex_numbers[starting_index]]
        current_subarray = [complex_numbers[starting_index]]
        for current_index in range(starting_index + 1, length_of_complex_numbers_list):
            if complex_numbers[current_index] not in distinct_values:
                distinct_values.append(complex_numbers[current_index])
            if len(distinct_values) > 3:
                break
            else:
                current_subarray.append((complex_numbers[current_index]))
        if len(current_subarray) > len(longest_subarray_of_complex_numbers_with_at_most_3_distinct_values):
            longest_subarray_of_complex_numbers_with_at_most_3_distinct_values = current_subarray
    return longest_subarray_of_complex_numbers_with_at_most_3_distinct_values


def get_longest_increasing_subsequence_considering_modulus(complex_numbers_modulus: list):
    """
    This function finds the longest increasing subsequence of the list of complex numbers considering the modulus of the complex numbers
    :param complex_numbers_modulus: the list of the modulus of the corresponding complex numbers
    :return: a list representing the longest increasing subsequence
    """
    complex_numbers_list_length = len(complex_numbers_modulus)
    increasing_length = [1] * complex_numbers_list_length
    increasing_sequence = [[num] for num in complex_numbers_modulus]

    for i in range(1, complex_numbers_list_length):
        for j in range(0, i):
            if complex_numbers_modulus[i] > complex_numbers_modulus[j] and increasing_length[i] < increasing_length[j] + 1:
                increasing_length[i] = increasing_length[j] + 1
                increasing_sequence[i] = increasing_sequence[j] + [complex_numbers_modulus[i]]

    max_length = max(increasing_length)
    max_index = increasing_length.index(max_length)
    longest_increasing_subsequence = increasing_sequence[max_index]

    return longest_increasing_subsequence


#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities


def print_menu():
    print("1. Add a complex number")
    print("2. Show all complex numbers")
    print("3. Length and elements of a longest subarray of numbers that contain at most 3 distinct values")
    print("4. The length and elements of a longest increasing subsequence, when considering each number's modulus")
    print("0. Exit")


def read_complex_number():
    real_number = int(input("Real number a = "))
    imaginary_number = int(input("Imaginary part b (* i) = "))
    # return create_complex_number_dictionary_representation(real_number, imaginary_number)
    return create_complex_number_list_representation(real_number, imaginary_number)


def add_complex_number_ui(data: list):
    complex_number = read_complex_number()
    data.append(complex_number)


def start():
    data_size = 10
    complex_numbers_data = generate_random_complex_numbers_list(data_size)
    # complex_numbers_data = generate_random_complex_numbers_dictionary(data_size)
    option_add_complex_number = 1
    option_show_all_numbers = 2
    option_longest_subarray = 3
    option_longest_increasing_subsequence = 4
    exit_option = 0
    valid_user_options = [str(option_add_complex_number), str(option_show_all_numbers), str(option_longest_subarray), str(option_longest_increasing_subsequence), str(exit_option)]
    while True:
        print_menu()
        user_option = input("Select from the menu: ").strip()
        try:
            if user_option not in valid_user_options:
                print("Insert a valid option...")
            elif user_option == str(option_add_complex_number):
                add_complex_number_ui(complex_numbers_data)
            elif user_option == str(option_show_all_numbers):
                for complex_number in complex_numbers_data:
                    print(list_to_string(complex_number))
                    # print(dictionary_to_string(complex_number))
            elif user_option == str(option_longest_subarray):
                longest_subarray = get_longest_subarray_of_with_at_most_3_distinct_values_naive(complex_numbers_data)
                print("There are " + str(len(longest_subarray)) + " elements in the longest subarray of complex numbers that contain at most 3 distinct values: ")
                for complex_number in longest_subarray:
                    print(list_to_string(complex_number))
                    # print(dictionary_to_string(complex_number))
            elif user_option == str(option_longest_increasing_subsequence):
                complex_numbers_modulus = replace_complex_numbers_with_their_modulus(complex_numbers_data)
                longest_increasing_modulus_subsequence = get_longest_increasing_subsequence_considering_modulus(complex_numbers_modulus)
                corresponding_complex_numbers = replace_modulus_with_their_corresponding_complex_numbers(longest_increasing_modulus_subsequence, complex_numbers_data)
                print("The " + str(len(corresponding_complex_numbers)) + " elements of the longest increasing subsequence, when considering each number's modulus: ")
                for complex_number in corresponding_complex_numbers:
                    print(list_to_string(complex_number))
                    # print(dictionary_to_string(complex_number))
            else:
                return None
        except ValueError as value_error:
            print(value_error)


if __name__ == "__main__":
    start()
# for A6 -> exercise 1
