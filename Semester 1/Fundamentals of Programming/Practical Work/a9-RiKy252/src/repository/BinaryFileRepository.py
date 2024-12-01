import pickle
import os
from src.repository.MemoryRepository import MemoryRepository


class BinaryFileRepository(MemoryRepository):
    def __init__(self):
        super().__init__()
        self.students_file_name = ""
        self.disciplines_file_name = ""
        self.grades_file_name = ""

    def set_students_file_name(self, new_students_file_name):
        self.students_file_name = new_students_file_name
        self.load_students()

    def set_disciplines_file_name(self, new_disciplines_file_name):
        self.disciplines_file_name = new_disciplines_file_name
        self.load_disciplines()

    def set_grades_file_name(self, new_grades_file_name):
        self.grades_file_name = new_grades_file_name
        self.load_grades()

    def load_students(self):
        try:
            if os.path.getsize(self.students_file_name) > 0:
                with open(self.students_file_name, "rb") as file:
                    self.students = pickle.load(file)
            else:
                self.students = []
        except (FileNotFoundError, EOFError):
            raise FileNotFoundError("Student file doesn't exist!")

    def load_disciplines(self):
        try:
            if os.path.getsize(self.disciplines_file_name) > 0:
                with open(self.disciplines_file_name, "rb") as file:
                    self.disciplines = pickle.load(file)
            else:
                self.disciplines = []
        except (FileNotFoundError, EOFError):
            raise FileNotFoundError("Discipline file doesn't exist!")

    def load_grades(self):
        try:
            if os.path.getsize(self.grades_file_name) > 0:
                with open(self.grades_file_name, "rb") as file:
                    self.grades = pickle.load(file)
            else:
                self.grades = []
        except (FileNotFoundError, EOFError):
            raise FileNotFoundError("Student file doesn't exist!")

    def _save_students_to_binary_file(self):
        with open(self.students_file_name, "wb") as file:
            pickle.dump(self.students, file)

    def _save_disciplines_to_binary_file(self):
        with open(self.disciplines_file_name, "wb") as file:
            pickle.dump(self.disciplines, file)

    def _save_grades_to_binary_file(self):
        with open(self.grades_file_name, "wb") as file:
            pickle.dump(self.grades, file)

    def add_student(self, student):
        super().add_student(student)
        self._save_students_to_binary_file()

    def add_discipline(self, discipline):
        super().add_discipline(discipline)
        self._save_disciplines_to_binary_file()

    def add_grade(self, grade):
        super().add_grade(grade)
        self._save_grades_to_binary_file()

    def remove_student(self, student_id):
        super().remove_student(student_id)
        self._save_students_to_binary_file()
        self._save_grades_to_binary_file()

    def remove_discipline(self, discipline_id):
        super().remove_discipline(discipline_id)
        self._save_disciplines_to_binary_file()
        self._save_grades_to_binary_file()

    def update_student(self, student_id, new_student_name):
        super().update_student(student_id, new_student_name)
        self._save_students_to_binary_file()

    def update_discipline(self, discipline_id, new_discipline_name):
        super().update_discipline(discipline_id, new_discipline_name)
        self._save_disciplines_to_binary_file()
