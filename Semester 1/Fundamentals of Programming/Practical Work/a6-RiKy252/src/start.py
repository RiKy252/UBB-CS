#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
from ui import *


def start():
    action_history = []
    complex_number_data = generate_random_complex_number(10)
    while True:
        try:
            user_input = get_user_input()
            complex_number_data = execute_command(user_input, complex_number_data, action_history)
        except ValueError as value_error:
            print(value_error)


start()

"""
Available commands:

add <number>
insert <number> at <position>

remove <position>
remove <start position> to <end position>
replace <old number> with <new number>

list
list real <start position> to <end position>
list modulo [ < | = | > ] <number>

filter real
filter modulo [ < | = | > ] <number>

undo
"""
