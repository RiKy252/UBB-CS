import re as regular_expression
from random import randint
from math import sqrt
#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
# complex number = a + bi


def is_valid_number(string_complex_number: str) -> bool:
    """
    This function checks if a string representation of a complex number is written in a+bi form
    :param string_complex_number: complex number to be verified
    :return: true if the number is correctly written, false otherwise
    """
    try:
        if "j" in string_complex_number:
            return False
        complex(string_complex_number.strip().replace("i", "j"))
        return True
    except ValueError:
        return False


def complex_number_list_representation(real_part: int, imaginary_part: int) -> list:
    """
    Used for representing complex numbers in this program
    :param real_part: the real part of the complex number
    :param imaginary_part: the imaginary part of the complex number
    :return: a list representing the complex number
    """
    return [real_part, imaginary_part]


def get_real_part(complex_number: list) -> int:
    real_part_index = 0
    return complex_number[real_part_index]


def get_imaginary_part(complex_number: list) -> int:
    imaginary_part_index = 1
    return complex_number[imaginary_part_index]


def generate_random_complex_number(generate_amount: int) -> list:
    """
    Generates some random complex numbers
    :param generate_amount: how many random complex numbers
    :return: a list representing the generated complex numbers
    Raises ValueError if the amount is less or equal to 0
    """
    if generate_amount <= 0:
        raise ValueError("You can't generate a negative amount of complex numbers")
    result = []
    for _ in range(generate_amount):
        real_part = randint(-30, 30)
        imaginary_part = randint(-30, 30)
        result.append(complex_number_list_representation(real_part, imaginary_part))
    return result


def string_representation(complex_number: list) -> str:
    """
    Provides a readable representation of a complex number
    :param complex_number: to be converted
    :return: string representation
    """
    real_part = get_real_part(complex_number)
    imaginary_part = get_imaginary_part(complex_number)
    if real_part == 0:
        return str(imaginary_part) + "i"
    elif imaginary_part < 0:
        return str(real_part) + str(imaginary_part) + "i"
    elif imaginary_part > 0:
        return str(real_part) + "+" + str(imaginary_part) + "i"
    elif imaginary_part == 0 and real_part == 0:
        return "0"
    elif imaginary_part == 0:
        return str(real_part)


def string_to_list(complex_number: str) -> list:
    """
    Transform a complex number from a string to a list
    :param complex_number: to be converted
    :return: the list representing the complex number
    Raises ValueError if complex number is not in a+bi form
    """
    if is_valid_number(complex_number):
        if complex_number == "i":
            real_part = 0
            imaginary_part = 1
            return complex_number_list_representation(real_part, imaginary_part)
        if complex_number == "-i":
            real_part = 0
            imaginary_part = -1
            return complex_number_list_representation(real_part, imaginary_part)
        if complex_number == "0":
            real_part = 0
            imaginary_part = 0
            return complex_number_list_representation(real_part, imaginary_part)

        extract_real_and_imaginary_part_pattern = r'-?\d+'
        extracted_complex_number_parts_string = regular_expression.findall(extract_real_and_imaginary_part_pattern, complex_number)
        extracted_complex_number_parts_int = [int(part) for part in extracted_complex_number_parts_string]
        if len(extracted_complex_number_parts_int) == 1:
            last_character_index = -1
            if complex_number[last_character_index] == "i" and not complex_number[last_character_index - 1] == '+' and not complex_number[last_character_index - 1] == '-':
                real_part = 0
                imaginary_part_index = 0
                imaginary_part = extracted_complex_number_parts_int[imaginary_part_index]
            elif complex_number[last_character_index] == "i" and complex_number[last_character_index - 1] == '+':
                real_part_index = 0
                real_part = extracted_complex_number_parts_int[real_part_index]
                imaginary_part = 1
            elif complex_number[last_character_index] == "i" and complex_number[last_character_index - 1] == '-':
                real_part_index = 0
                real_part = extracted_complex_number_parts_int[real_part_index]
                imaginary_part = -1
            else:
                imaginary_part = 0
                real_part_index = 0
                real_part = extracted_complex_number_parts_int[real_part_index]
        else:
            real_part = get_real_part(extracted_complex_number_parts_int)
            imaginary_part = get_imaginary_part(extracted_complex_number_parts_int)
        return complex_number_list_representation(real_part, imaginary_part)
    else:
        raise ValueError("Complex number must be in a+bi form")


def get_complex_number_modulus(complex_number):
    """
    This function gets the modulus of a complex number
    :param complex_number: modulus to be calculated for
    :return: the modulus
    """
    real_part = get_real_part(complex_number)
    imaginary_part = get_imaginary_part(complex_number)
    real_part_squared = real_part ** 2
    imaginary_part_squared = imaginary_part ** 2
    complex_number_modulus = sqrt(real_part_squared + imaginary_part_squared)
    return complex_number_modulus


def replace_complex_numbers_with_their_modulus(complex_numbers_data: list):
    """
    This function takes the data of complex numbers and replace each number with their corresponding modulus
    :param complex_numbers_data: the data to be processed
    :return: the new data with the modulus of the complex numbers at corresponding indexes
    """
    complex_numbers_modulus = []
    for complex_number in complex_numbers_data:
        complex_numbers_modulus.append(get_complex_number_modulus(complex_number))
    return complex_numbers_modulus


def filter_real(complex_numbers_data: list):
    """
    This function filters the data of complex numbers having imaginary part 0
    :param complex_numbers_data: data to be processed
    :return: the filtered list
    """
    filtered_data = []
    for complex_number in complex_numbers_data:
        imaginary_part = get_imaginary_part(complex_number)
        if imaginary_part == 0:
            filtered_data.append(complex_number)
    return filtered_data


def filter_number_modulus(complex_numbers_data: list, comparison_sign: str, comparison_number: int):
    """
    This function filters the data of complex numbers keeping only the numbers that have specific modulus value, depending on the sign and number
    :param complex_numbers_data: data to be processed
    :param comparison_sign: sign to compare complex numbers in data with the comparison number
    :param comparison_number: represents the modulus extremum depending on sign
    :return: the filtered list
    """
    valid_comparison_signs = ["<", "=", ">"]
    filtered_list = []
    if comparison_sign not in valid_comparison_signs:
        raise ValueError("Invalid comparison sign!")
    match comparison_sign:
        case "<":
            for complex_number in complex_numbers_data:
                if get_complex_number_modulus(complex_number) < comparison_number:
                    filtered_list.append(complex_number)
        case "=":
            for complex_number in complex_numbers_data:
                if get_complex_number_modulus(complex_number) == comparison_number:
                    filtered_list.append(complex_number)
        case ">":
            for complex_number in complex_numbers_data:
                if get_complex_number_modulus(complex_number) > comparison_number:
                    filtered_list.append(complex_number)
    return filtered_list


def add_complex_number(complex_number: str, data: list):
    """
    Appends the complex number to the data and returns the data list
    Raises ValueError if complex number not in a+bi form
    """
    if is_valid_number(complex_number):
        complex_number = string_to_list(complex_number)
        data.append(complex_number)
    else:
        raise ValueError("Complex number must be in a+bi form")
    return data


def test_add_complex_number():
    assert add_complex_number("2+3i", [[2, 0]]) == [[2, 0], [2, 3]]
    assert add_complex_number("0", []) == [[0, 0]]
    assert add_complex_number("7i", [[2, 3], [1, 0], [5, 6]]) == [[2, 3], [1, 0], [5, 6], [0, 7]]
    assert add_complex_number("-3+4i", []) == [[-3, 4]]
    assert add_complex_number("-7-10i", [[-3, 4], [0, 1], [1, 0]]) == [[-3, 4], [0, 1], [1, 0], [-7, -10]]


def insert_complex_number_at_position(complex_number: str, position: int, data: list):
    """
    Inserts the complex number in the data at the specified position and returns the data list
    Raises ValueError if position is not valid or complex number not in a+bi form
    """
    if is_valid_number(complex_number) and 0 <= position <= len(data):
        complex_number = string_to_list(complex_number)
        data.insert(position, complex_number)
    else:
        raise ValueError("Complex number must be in a+bi form and the position must be within the range of the list")
    return data


def test_insert_complex_number_at_position():
    assert insert_complex_number_at_position("2i", 2, [[4, 3], [5, 2], [7, 4], [2, 5], [0, 0], [1, 0]]) == [[4, 3], [5, 2], [0, 2], [7, 4], [2, 5], [0, 0], [1, 0]]
    assert insert_complex_number_at_position("1+5i", 6, [[1, 3], [4, 2], [3, 4], [2, 11], [0, 3], [1, 5]]) == [[1, 3], [4, 2], [3, 4], [2, 11], [0, 3], [1, 5], [1, 5]]
    assert insert_complex_number_at_position("-3-5i", 3, [[4, 7], [5, 8], [2, 4], [2, 1], [7, 7], [6, 6]]) == [[4, 7], [5, 8], [2, 4], [-3, -5], [2, 1], [7, 7], [6, 6]]
    assert insert_complex_number_at_position("-5+i", 4, [[-4, -3], [-5, 2], [7, -4], [2, 19]]) == [[-4, -3], [-5, 2], [7, -4], [2, 19], [-5, 1]]
    assert insert_complex_number_at_position("2i", 1, [[0, 0]]) == [[0, 0], [0, 2]]


def remove_element_from_position(complex_numbers_data: list, position: int):
    """
    Removes the element from the specified position in the data list and returns the data list
    Raises ValueError if the position specified is not valid for the data list in case
    """
    if position < 0 or position >= len(complex_numbers_data):
        raise ValueError("The position must be within the range of the list")
    complex_numbers_data.pop(position)
    return complex_numbers_data


def test_remove_element_from_position():
    assert remove_element_from_position([[4, 3], [5, 2], [7, 4], [2, 5], [0, 0], [1, 0]], 1) == [[4, 3], [7, 4], [2, 5], [0, 0], [1, 0]]
    assert remove_element_from_position([[1, 3], [4, 2], [3, 4], [2, 11], [0, 3], [1, 5]], 2) == [[1, 3], [4, 2], [2, 11], [0, 3], [1, 5]]
    assert remove_element_from_position([[4, 7], [5, 8], [2, 4], [2, 1], [7, 7], [6, 6]], 3) == [[4, 7], [5, 8], [2, 4], [7, 7], [6, 6]]
    assert remove_element_from_position([[-4, -3], [-5, 2], [7, -4], [2, 19]], 3) == [[-4, -3], [-5, 2], [7, -4]]
    assert remove_element_from_position([[5, 90]], 0) == []


def remove_start_position_to_end_position(complex_numbers_data: list, start_position: int, end_position: int):
    """
    Removes the elements from the start position index until end position index, including endpoints and returns the data list
    Raises ValueError if one/both of the positions are not within the data range, or start position > end position
    """
    if start_position > end_position:
        raise ValueError("Start position must be <= to the end position")
    if start_position < 0 or end_position >= len(complex_numbers_data):
        raise ValueError("Positions are not within the complex numbers data range")
    index = start_position
    for _ in range(start_position, end_position + 1):
        complex_numbers_data.pop(index)
    return complex_numbers_data


def test_remove_start_position_to_end_position():
    assert remove_start_position_to_end_position([[4, 3], [5, 2], [7, 4], [2, 5], [0, 0], [1, 0]], 1, 3) == [[4, 3], [0, 0], [1, 0]]
    assert remove_start_position_to_end_position([[1, 3], [4, 2], [3, 4], [2, 11], [0, 3], [1, 5]], 2, 4) == [[1, 3], [4, 2], [1, 5]]
    assert remove_start_position_to_end_position([[4, 7], [5, 8], [2, 4], [2, 1], [7, 7], [6, 6]], 0, 4) == [[6, 6]]
    assert remove_start_position_to_end_position([[-4, -3], [-5, 2], [7, -4], [2, 19]], 0, 2) == [[2, 19]]
    assert remove_start_position_to_end_position([[75, -20]], 0, 0) == []


def replace_old_number_with_new_number(complex_numbers_data: list, old_complex_number: list, new_complex_number: list):
    """
    Replaces all occurrences of old complex number with the new complex number value and returns the data list
    Raises ValueError if the old complex number does not belong to the data
    """
    if old_complex_number not in complex_numbers_data:
        raise ValueError(string_representation(old_complex_number) + " does not belong to the data")
    for index in range(len(complex_numbers_data)):
        if complex_numbers_data[index] == old_complex_number:
            complex_numbers_data[index] = new_complex_number
    return complex_numbers_data


def test_replace_old_number_with_new_number():
    assert replace_old_number_with_new_number([[4, 3], [5, 2], [4, 3], [2, 5], [0, 0], [4, 3]], [4, 3], [0, 1]) == [[0, 1], [5, 2], [0, 1], [2, 5], [0, 0], [0, 1]]
    assert replace_old_number_with_new_number([[1, 3], [4, 2], [3, 4], [4, 2], [4, 2], [1, 5]], [4, 2], [0, 0]) == [[1, 3], [0, 0], [3, 4], [0, 0], [0, 0], [1, 5]]
    assert replace_old_number_with_new_number([[6, 6], [5, 8], [6, 6], [6, 6], [7, 7], [6, 6]], [6, 6], [2, 3]) == [[2, 3], [5, 8], [2, 3], [2, 3], [7, 7], [2, 3]]
    assert replace_old_number_with_new_number([[0, 0], [0, 2], [0, 0], [0, 0]], [0, 0], [25, -2]) == [[25, -2], [0, 2], [25, -2], [25, -2]]
    assert replace_old_number_with_new_number([[53, 12]], [53, 12], [1, 2]) == [[1, 2]]


test_add_complex_number()
test_insert_complex_number_at_position()
test_remove_element_from_position()
test_remove_start_position_to_end_position()
test_replace_old_number_with_new_number()
