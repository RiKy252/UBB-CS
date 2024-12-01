from src.repository.MemoryRepository import MemoryRepository
from src.domain.student import Student
from src.domain.discipline import Discipline
from src.domain.grades import Grades
import os


class TextFileRepository(MemoryRepository):
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
                with open(self.students_file_name, "r") as file:
                    lines = file.readlines()
                    for line in lines:
                        line = line.strip().split(",")
                        if len(line) == 2:
                            student_id_index = 0
                            student_name_index = 1
                            student = Student(int(line[student_id_index]), line[student_name_index])
                            self.students.append(student)
        except (FileNotFoundError, EOFError):
            raise FileNotFoundError("Student file doesn't exist!")

    def load_disciplines(self):
        try:
            if os.path.getsize(self.disciplines_file_name) > 0:
                with open(self.disciplines_file_name, "r") as file:
                    lines = file.readlines()
                    for line in lines:
                        line = line.strip().split(",")
                        if len(line) == 2:
                            discipline_id_index = 0
                            discipline_name_index = 1
                            discipline = Discipline(int(line[discipline_id_index]), line[discipline_name_index])
                            self.disciplines.append(discipline)
        except (FileNotFoundError, EOFError):
            raise FileNotFoundError("Discipline file doesn't exist!")

    def load_grades(self):
        try:
            if os.path.getsize(self.grades_file_name) > 0:
                with open(self.grades_file_name, "r") as file:
                    lines = file.readlines()
                    for line in lines:
                        line = line.strip().split(",")
                        if len(line) == 3:
                            discipline_id_index = 0
                            student_id_index = 1
                            grade_value_index = 2
                            grade = Grades(int(line[discipline_id_index]), int(line[student_id_index]), float(line[grade_value_index]))
                            self.grades.append(grade)
        except (FileNotFoundError, EOFError):
            raise FileNotFoundError("Grades file doesn't exist!")

    def add_student(self, student):
        super().add_student(student)
        with open(self.students_file_name, "a") as file:
            file.write(str(student.student_id) + "," + student.name + "\n")

    def add_discipline(self, discipline):
        super().add_discipline(discipline)
        with open(self.disciplines_file_name, "a") as file:
            file.write(str(discipline.discipline_id) + "," + discipline.name + "\n")

    def add_grade(self, grade):
        super().add_grade(grade)
        with open(self.grades_file_name, "a") as file:
            file.write(str(grade.discipline_id) + "," + str(grade.student_id) + "," + str(grade.grade_value) + "\n")

    def remove_student(self, student_id):
        super().remove_student(student_id)
        with open(self.students_file_name, "w") as file:
            for student in self.students:
                file.write(str(student.student_id) + "," + student.name + "\n")
        with open(self.grades_file_name, "w") as file:
            for grade in self.grades:
                file.write(str(grade.discipline_id) + "," + str(grade.student_id) + "," + str(grade.grade_value) + "\n")

    def remove_discipline(self, discipline_id):
        super().remove_discipline(discipline_id)
        with open(self.disciplines_file_name, "w") as file:
            for discipline in self.disciplines:
                file.write(str(discipline.discipline_id) + "," + discipline.name + "\n")
        with open(self.grades_file_name, "w") as file:
            for grade in self.grades:
                file.write(str(grade.discipline_id) + "," + str(grade.student_id) + "," + str(grade.grade_value) + "\n")

    def update_student(self, student_id, new_student_name):
        super().update_student(student_id, new_student_name)
        with open(self.students_file_name, "w") as file:
            for student in self.students:
                file.write(str(student.student_id) + "," + student.name + "\n")

    def update_discipline(self, discipline_id, new_discipline_name):
        super().update_discipline(discipline_id, new_discipline_name)
        with open(self.disciplines_file_name, "w") as file:
            for discipline in self.disciplines:
                file.write(str(discipline.discipline_id) + "," + discipline.name + "\n")
