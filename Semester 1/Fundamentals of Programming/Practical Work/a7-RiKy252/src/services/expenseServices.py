from src.repository.expenseRepository import ExpenseRepository
from src.repository.expenseRepositoryFile import ExpenseRepositoryFile
from src.repository.expenseRepositoryBinary import ExpenseRepositoryBinary
from src.repository.expenseRepositoryJSON import ExpenseRepositoryJSON


class ExpensesServices(ExpenseRepository):

    def __init__(self, repository_type):
        super().__init__()
        self.repository = None
        self.select_repository(repository_type)

    def select_repository(self, repository_type):
        if repository_type == ExpenseRepository:
            self.repository = ExpenseRepository()
        elif repository_type == ExpenseRepositoryFile:
            self.repository = ExpenseRepositoryFile()
        elif repository_type == ExpenseRepositoryBinary:
            self.repository = ExpenseRepositoryBinary()
        elif repository_type == ExpenseRepositoryJSON:
            self.repository = ExpenseRepositoryJSON()
        else:
            raise ValueError("Invalid repository type")

    def change_repository(self, repository_type):
        self.select_repository(repository_type)

    def add_expense(self, expense):
        """
        This function adds a specified expense to the current repository
        :param expense: the expense to be added
        In case of ValueError it prints out the error
        """
        try:
            self.repository.add_expense(expense)
        except ValueError as value_error:
            print(value_error)

    @property
    def all(self):
        return self.repository.all

    def filter(self, value):
        self.repository.filter(value)

    def undo(self):
        self.repository.undo()
        