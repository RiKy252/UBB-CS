from src.repository.MemoryRepository import RepositoryError
from src.domain.student import Student
from src.domain.discipline import Discipline


class AddStudentCommand:
    def __init__(self, service, student):
        self.service = service
        self.student = student

    def execute(self):
        self.service.add_student(self.student)

    def undo(self):
        self.service.remove_student(self.student.student_id)


class RemoveStudentCommand:
    def __init__(self, student_service, grades_service, student):
        self.student_service = student_service
        self.grades_service = grades_service
        self.student = student
        self.grade_list = []
        for grade in self.student_service.repository.grades:
            if self.student.student_id == grade.student_id:
                self.grade_list.append(grade)

    def execute(self):
        self.student_service.remove_student(self.student.student_id)

    def undo(self):
        self.student_service.add_student(self.student)
        for grade in self.grade_list:
            self.grades_service.add_grade(grade)


class AddDisciplineCommand:
    def __init__(self, service, discipline):
        self.service = service
        self.discipline = discipline

    def execute(self):
        self.service.add_discipline(self.discipline)

    def undo(self):
        self.service.remove_discipline(self.discipline.discipline_id)


class RemoveDisciplineCommand:
    def __init__(self, discipline_service, grades_service, discipline):
        self.discipline_service = discipline_service
        self.grades_service = grades_service
        self.discipline = discipline
        self.grade_list = []
        for grade in self.discipline_service.repository.grades:
            if self.discipline.discipline_id == grade.discipline_id:
                self.grade_list.append(grade)

    def execute(self):
        self.discipline_service.remove_discipline(self.discipline.discipline_id)

    def undo(self):
        self.discipline_service.add_discipline(self.discipline)
        for grade in self.grade_list:
            self.grades_service.add_grade(grade)


class UpdateStudentCommand:
    def __init__(self, service, student, new_name):
        self.service = service
        self.student = student
        self.new_name = new_name
        self.old_name = self.student.name

    def execute(self):
        self.service.update_student(self.student.student_id, self.new_name)

    def undo(self):
        student = Student(self.student.student_id, self.new_name)
        self.service.update_student(student.student_id, self.old_name)


class UpdateDisciplineCommand:
    def __init__(self, service, discipline, new_name):
        self.service = service
        self.discipline = discipline
        self.new_name = new_name
        self.old_name = self.discipline.name

    def execute(self):
        self.service.update_discipline(self.discipline.discipline_id, self.new_name)

    def undo(self):
        discipline = Discipline(self.discipline.discipline_id, self.new_name)
        self.service.update_discipline(discipline.discipline_id, self.old_name)


class UndoRedoService:
    def __init__(self, student_service, discipline_service, grades_service):
        self.student_service = student_service
        self.discipline_service = discipline_service
        self.grades_service = grades_service
        self.undo_stack = []
        self.redo_stack = []

    def execute_command(self, command):
        self.undo_stack.append(command)
        self.redo_stack = []

    def undo(self):
        if self.undo_stack:
            command = self.undo_stack.pop()
            command.undo()
            self.redo_stack.append(command)
        else:
            raise RepositoryError("No operations to be undone")

    def redo(self):
        if self.redo_stack:
            command = self.redo_stack.pop()
            command.execute()
            self.undo_stack.append(command)
        else:
            raise RepositoryError("No operations to be redone")
