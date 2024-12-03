from src.repository.expenseRepository import ExpenseRepository
from src.domain.expense import Expense
import os


class ExpenseRepositoryFile(ExpenseRepository):
    def __init__(self):
        super().__init__()
        self.file_name = "TextFile.txt"
        self.load_expenses()

    def load_expenses(self):
        try:
            if os.path.getsize(self.file_name) > 0:
                with open(self.file_name, "r") as file:
                    lines = file.readlines()
                    for line in lines:
                        line = line.strip().split(",")
                        if len(line) == 3:
                            day_index, amount_index, type_index = 0, 1, 2
                            expense = Expense(int(line[day_index]), int(line[amount_index]), line[type_index])
                            self.expenses.append(expense)
        except (FileNotFoundError, EOFError):
            self.expenses = []

    def add_expense(self, expense):
        super().add_expense(expense)
        with open(self.file_name, "a") as file:
            file.write(str(expense.day) + "," + str(expense.amount) + "," + expense.expense_type + "\n")

    def filter(self, value):
        super().filter(value)
        with open(self.file_name, "w") as file:
            for expense in self.expenses:
                file.write(str(expense.day) + "," + str(expense.amount) + "," + expense.expense_type + "\n")

    def undo(self):
        super().undo()
        with open(self.file_name, "w") as file:
            for expense in self.expenses:
                file.write(str(expense.day) + "," + str(expense.amount) + "," + expense.expense_type + "\n")
