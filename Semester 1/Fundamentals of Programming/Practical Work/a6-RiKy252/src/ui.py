#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
import copy

from functions import *


def get_user_input():
    user_input = input("Write a command: ")
    return user_input


def add_user_complex_number(complex_number: str, complex_numbers_data: list):
    add_complex_number(complex_number, complex_numbers_data)


def insert_user_complex_number(complex_number: str, position: int, complex_numbers_data: list):
    try:
        insert_complex_number_at_position(complex_number, position, complex_numbers_data)
    except ValueError as value_error:
        print(value_error)


def display_all_numbers(complex_numbers_data: list):
    for complex_number in complex_numbers_data:
        print(string_representation(complex_number))


def display_real_number(start_position: int, end_position: int, complex_numbers_data: list):
    if start_position > end_position:
        raise ValueError("Start position must be <= to the end position")
    if start_position < 0 or end_position >= len(complex_numbers_data):
        raise ValueError("Positions are not within the complex numbers data range")
    for index in range(start_position, end_position + 1):
        real_part = get_real_part(complex_numbers_data[index])
        print(real_part)


def display_numbers_modulus(comparison_sign: str, comparison_number: int, complex_numbers_data: list):
    valid_comparison_signs = ["<", "=", ">"]
    if comparison_sign not in valid_comparison_signs:
        raise ValueError("Invalid comparison sign!")
    match comparison_sign:
        case "<":
            for complex_number in complex_numbers_data:
                if get_complex_number_modulus(complex_number) < comparison_number:
                    print(string_representation(complex_number))
        case "=":
            for complex_number in complex_numbers_data:
                if get_complex_number_modulus(complex_number) == comparison_number:
                    print(string_representation(complex_number))
        case ">":
            for complex_number in complex_numbers_data:
                if get_complex_number_modulus(complex_number) > comparison_number:
                    print(string_representation(complex_number))


def execute_command(user_input: str, complex_number_data: list, data_history: list):
    user_input = user_input.split()
    command_index = 0
    command = user_input[command_index]
    valid_commands = ["add", "insert", "remove", "replace", "list", "filter", "undo"]
    try:
        if command not in valid_commands:
            raise ValueError("Command is not valid")
        else:
            match command:
                case "add":
                    add_expected_input_length = 2
                    if len(user_input) == add_expected_input_length:
                        complex_number_index = 1
                        data_history.append(copy.deepcopy(complex_number_data))
                        add_user_complex_number(user_input[complex_number_index], complex_number_data)
                    elif not len(user_input) == add_expected_input_length:
                        raise ValueError("Input length not expected")
                    return complex_number_data
                case "insert":
                    insert_expected_input_length = 4
                    expected_at_index = 2
                    if user_input[expected_at_index] == "at" and len(user_input) == insert_expected_input_length:
                        complex_number_index = 1
                        position_value_index = 3
                        data_history.append(complex_number_data.copy())
                        insert_user_complex_number(user_input[complex_number_index], int(user_input[position_value_index]), complex_number_data)
                        return complex_number_data
                    elif "at" not in user_input:
                        raise ValueError("Incomplete insert command")
                    elif not len(user_input) == insert_expected_input_length:
                        raise ValueError("Input length not expected")
                case "remove":
                    remove_position_expected_length = 2
                    remove_start_position_to_end_position_expected_length = 4
                    expected_to_index = 2
                    if len(user_input) == remove_position_expected_length:
                        position_value_index = 1
                        data_history.append(complex_number_data.copy())
                        position = int(user_input[position_value_index])
                        remove_element_from_position(complex_number_data, position)
                        return complex_number_data
                    elif len(user_input) == remove_start_position_to_end_position_expected_length and user_input[expected_to_index] == "to":
                        start_position_value_index = 1
                        end_position_value_index = 3
                        data_history.append(complex_number_data.copy())
                        start_position = int(user_input[start_position_value_index])
                        end_position = int(user_input[end_position_value_index])
                        remove_start_position_to_end_position(complex_number_data, start_position, end_position)
                        return complex_number_data
                case "replace":
                    replace_expected_length = 4
                    expected_with_index = 2
                    if len(user_input) == replace_expected_length and user_input[expected_with_index] == "with":
                        old_number_index = 1
                        new_number_index = 3
                        data_history.append(copy.deepcopy(complex_number_data))
                        old_number = string_to_list(user_input[old_number_index])
                        new_number = string_to_list(user_input[new_number_index])
                        replace_old_number_with_new_number(complex_number_data, old_number, new_number)
                        return complex_number_data
                case "list":
                    display_all_numbers_expected_length = 1
                    display_real_numbers_expected_length = 5
                    real_expected_index = 1
                    to_expected_index = 3
                    modulo_expected_index = 1
                    display_modulo_expected_length = 4
                    if len(user_input) == display_all_numbers_expected_length:
                        display_all_numbers(complex_number_data)
                    elif len(user_input) == display_real_numbers_expected_length and user_input[real_expected_index] == "real" and user_input[to_expected_index] == "to":
                        start_position_index = 2
                        end_position_index = 4
                        display_real_number(int(user_input[start_position_index]), int(user_input[end_position_index]), complex_number_data)
                    elif len(user_input) == display_modulo_expected_length and user_input[modulo_expected_index] == "modulo":
                        comparison_sign_index = 2
                        comparison_number_index = 3
                        display_numbers_modulus(user_input[comparison_sign_index], int(user_input[comparison_number_index]), complex_number_data)
                    else:
                        raise ValueError("Incomplete command!")
                case "filter":
                    filter_real_expected_length = 2
                    real_expected_index = 1
                    filter_modulo_expected_length = 4
                    modulo_expected_index = 1
                    if len(user_input) == filter_real_expected_length and user_input[real_expected_index] == "real":
                        data_history.append(copy.deepcopy(complex_number_data))
                        return filter_real(complex_number_data)
                    elif len(user_input) == filter_real_expected_length:
                        raise ValueError("Incorrect command!")
                    elif len(user_input) == filter_modulo_expected_length and user_input[modulo_expected_index] == "modulo":
                        comparison_sign_index = 2
                        comparison_number_index = 3
                        data_history.append(copy.deepcopy(complex_number_data))
                        return filter_number_modulus(complex_number_data, user_input[comparison_sign_index], int(user_input[comparison_number_index]))
                    else:
                        raise ValueError("Incomplete command!")
                case "undo":
                    undo_expected_length = 1
                    last_element_index = -1
                    if len(user_input) == undo_expected_length and len(data_history) > 0:
                        complex_number_data = data_history[last_element_index]
                        data_history.pop()
                        return complex_number_data
                    elif len(user_input) == undo_expected_length and len(data_history) == 0:
                        raise ValueError("You cannot undo anymore!")
                    else:
                        raise ValueError("Unknown command!")
    except ValueError as value_error:
        print(value_error)
    return complex_number_data
