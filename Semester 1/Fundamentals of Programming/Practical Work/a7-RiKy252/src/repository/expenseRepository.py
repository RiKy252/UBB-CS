import copy
import unittest
from src.domain.expense import Expense


class ExpenseRepository:
    def __init__(self):
        self.expenses = []
        self.undo_stack = []

    @staticmethod
    def check_day(day):
        if day < 1:
            raise ValueError("Day must be between 1-30!")
        if day > 30:
            raise ValueError("Day must be between 1-30!")
        return True

    @staticmethod
    def check_amount(amount):
        if not isinstance(amount, int):
            raise ValueError("Amount must be an integer!")
        return True

    def add_expense(self, expense):
        self.undo_stack.append(copy.deepcopy(self.expenses))
        try:
            self.expenses.append(expense)
        except ValueError as value_error:
            print(value_error)

    @property
    def all(self):
        message = ""
        if self.expenses:
            for expense in self.expenses:
                message += expense.__str__()
                message += "\n"
        else:
            message = "The repository is empty!"
        return message[:-1]

    def filter(self, value):
        self.undo_stack.append(copy.deepcopy(self.expenses))
        expenses_to_remove = []
        for expense in self.expenses:
            expense_amount = expense.amount
            if expense_amount <= value:
                expenses_to_remove.append(expense)
        for expense in expenses_to_remove:
            self.expenses.remove(expense)

    def undo(self):
        self.expenses = copy.deepcopy(self.undo_stack.pop())


class TestExpenseRepository(unittest.TestCase):
    def setUp(self):
        self.expense_repo = ExpenseRepository()

    def test_add_expense(self):
        expense = Expense(1, 10, "food")
        self.expense_repo.add_expense(expense)
        self.assertEqual(self.expense_repo.expenses, [expense])
