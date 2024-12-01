from src.repository.expenseRepository import ExpenseRepository
import json
import os

from src.domain.expense import Expense


class ExpenseRepositoryJSON(ExpenseRepository):
    def __init__(self):
        super().__init__()
        self.file_name = "expenses.json"
        self.load_expenses()

    def load_expenses(self):
        try:
            if os.path.exists(self.file_name) and os.path.getsize(self.file_name) > 0:
                with open(self.file_name, "r") as file:
                    data = json.load(file)
                    self.expenses = [Expense(file_object['day'], file_object['amount'], file_object['expense_type']) for file_object in data]

            else:
                self.expenses = []
        except (FileNotFoundError, json.JSONDecodeError):
            self.expenses = []

    def save_expenses(self):
        with open(self.file_name, "w") as file:
            data = [{'day': expense.day, 'amount': expense.amount, 'expense_type': expense.expense_type} for expense in self.expenses]
            json.dump(data, file, indent=2)

    def add_expense(self, expense):
        super().add_expense(expense)
        self.save_expenses()

    def filter(self, value):
        super().filter(value)
        self.save_expenses()

    def undo(self):
        super().undo()
        self.save_expenses()
