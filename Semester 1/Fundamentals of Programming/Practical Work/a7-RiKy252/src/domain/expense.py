class Expense:
    def __init__(self, day, amount, expense_type):
        self.__day = day
        self.__amount = amount
        self.__expense_type = expense_type

    @property
    def day(self):
        return self.__day

    @property
    def amount(self):
        return self.__amount

    @property
    def expense_type(self):
        return self.__expense_type

    def __str__(self):
        return "Day: " + str(self.day) + ", amount: " + str(self.amount) + ", type: " + self.__expense_type
