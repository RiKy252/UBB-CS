from random import randint
from random import uniform
from unittest import TestCase
from src.domain.student import Student
from src.domain.discipline import Discipline


class Grades:
    def __init__(self, discipline_id: int, student_id: int, grade_value: float):
        self._discipline_id = discipline_id
        self._student_id = student_id
        self._grade_value = grade_value

    @property
    def discipline_id(self):
        return self._discipline_id

    @property
    def student_id(self):
        return self._student_id

    @property
    def grade_value(self):
        return self._grade_value

    def __eq__(self, other):
        if not isinstance(other, Grades):
            return False
        return other.student_id == self.student_id and other.discipline_id == self.discipline_id and other.grade_value == self._grade_value


class TestGrade(TestCase):
    def test_grade_discipline_id(self):
        grade = Grades(10, 5, 8.72)
        self.assertEqual(grade.discipline_id, 10)

    def test_grade_student_id(self):
        grade = Grades(20, 101, 7.67)
        self.assertEqual(grade.student_id, 101)

    def test_grade_value(self):
        grade = Grades(1, 1, 9.999)
        self.assertEqual(grade.grade_value, 9.999)


def generate_random_grades(number_of_grades: int, data):
    students_data = data.students
    disciplines_data = data.disciplines
    max_index_of_students = len(students_data) - 1
    max_index_of_disciplines = len(disciplines_data) - 1
    start_index = 0
    minimum_grade_value = 0.0
    maximum_grade_value = 10.0
    for _ in range(number_of_grades):
        random_discipline = disciplines_data[randint(start_index, max_index_of_disciplines)]
        discipline_id = random_discipline.discipline_id
        random_student = students_data[randint(start_index, max_index_of_students)]
        student_id = random_student.student_id
        random_grade_value = uniform(minimum_grade_value, maximum_grade_value)
        current_grade = Grades(discipline_id, student_id, random_grade_value)
        data.add_grade(current_grade)
