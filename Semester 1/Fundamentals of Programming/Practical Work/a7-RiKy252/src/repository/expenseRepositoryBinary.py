import pickle
import os
from src.repository.expenseRepository import ExpenseRepository


class ExpenseRepositoryBinary(ExpenseRepository):
    def __init__(self):
        super().__init__()
        self.file_name = "BinaryFile.txt"
        self.load_expenses()

    def load_expenses(self):
        try:
            if os.path.getsize(self.file_name) > 0:
                with open(self.file_name, "rb") as file:
                    self.expenses = pickle.load(file)
            else:
                self.expenses = []
        except (FileNotFoundError, EOFError):
            self.expenses = []

    def add_expense(self, expense):
        super().add_expense(expense)
        self._save_to_binary_file()

    def filter(self, value):
        super().filter(value)
        self._save_to_binary_file()

    def undo(self):
        super().undo()
        self._save_to_binary_file()

    def _save_to_binary_file(self):
        with open(self.file_name, "wb") as file:
            pickle.dump(self.expenses, file)
