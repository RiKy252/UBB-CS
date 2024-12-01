# TEST
class Assignment:
    def __init__(self, assignment_id, student_name, solution):
        self.__assignment_id = assignment_id
        self.__student_name = student_name
        self.__solution = solution

    @property
    def assigment_id(self):
        return self.__assignment_id

    @property
    def student_name(self):
        return self.__student_name

    @property
    def solution(self):
        return self.__solution

    def __str__(self):
        return "ID: " + str(self.assigment_id) + ", name: " + self.student_name + ", solution: " + self.solution
