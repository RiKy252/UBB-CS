from src.domain.expense import Expense
from src.repository.expenseRepository import ExpenseRepository
from src.services.expenseServices import ExpensesServices
from src.repository.expenseRepositoryFile import ExpenseRepositoryFile
from src.repository.expenseRepositoryBinary import ExpenseRepositoryBinary
from src.repository.expenseRepositoryJSON import ExpenseRepositoryJSON


class UI:
    def __init__(self, services):
        self.service = services
        self.__menu_entry = None

    @staticmethod
    def menu():
        print("1. Add an expense")
        print("2. Display expenses")
        print("3. Filter expenses")
        print("4. Undo")
        print("0. Exit program")

    def start(self):
        add_expense_menu_option = 1
        display_expenses_menu_option = 2
        filter_expenses_menu_option = 3
        undo_menu_option = 4
        exit_program_menu_option = 0
        valid_user_inputs = [add_expense_menu_option, display_expenses_menu_option, filter_expenses_menu_option, undo_menu_option, exit_program_menu_option]
        while True:
            self.menu()
            try:
                self.__menu_entry = int(input("Insert an option from the menu: "))
                if self.__menu_entry not in valid_user_inputs:
                    raise ValueError("Please insert a valid option from the menu!")
                if self.__menu_entry == add_expense_menu_option:
                    try:
                        user_day_input = int(input("Enter the expense day: "))
                        self.service.repository.check_day(user_day_input)
                        user_amount_input = int(input("Enter the expense amount: "))
                        self.service.repository.check_amount(user_amount_input)
                        user_type_input = input("Enter the expense type: ")
                        expense = Expense(user_day_input, user_amount_input, user_type_input)
                        self.service.add_expense(expense)
                    except ValueError as value_error:
                        print(value_error)
                elif self.__menu_entry == display_expenses_menu_option:
                    print(self.service.all)
                elif self.__menu_entry == filter_expenses_menu_option:
                    try:
                        user_value = int(input("Enter the value for the expenses to be filtered: "))
                        self.service.filter(user_value)
                    except ValueError as value_error:
                        print(value_error)
                elif self.__menu_entry == undo_menu_option:
                    try:
                        assert self.service.repository.undo_stack
                        self.service.undo()
                    except AssertionError:
                        print("Cannot undo past the first operation!")
                else:
                    break
            except ValueError as value_error:
                print(value_error)


def programmatically_generate_entries(number_of_generations: int, data):
    for index in range(1, number_of_generations + 1):
        day = index
        amount = index
        expense_type = "some type" + str(index)
        expense = Expense(day, amount, expense_type)
        data.add_expense(expense)


def main():
    from settings import memory, text_file, binary_file, json
    data = ExpensesServices(ExpenseRepository)
    number_of_generations = 10
    if memory:
        programmatically_generate_entries(number_of_generations, data)
    elif text_file:
        data.change_repository(ExpenseRepositoryFile)
        if not data.repository.expenses:
            programmatically_generate_entries(number_of_generations, data)
    elif binary_file:
        data.change_repository(ExpenseRepositoryBinary)
        if not data.repository.expenses:
            programmatically_generate_entries(number_of_generations, data)
    elif json:
        data.change_repository(ExpenseRepositoryJSON)
        if not data.repository.expenses:
            programmatically_generate_entries(number_of_generations, data)
    user = UI(data)
    user.start()


main()
