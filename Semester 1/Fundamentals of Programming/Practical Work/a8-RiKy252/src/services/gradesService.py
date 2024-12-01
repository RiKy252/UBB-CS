from src.repository.MemoryRepository import RepositoryError
from src.repository.MemoryRepository import MemoryRepository
from src.domain.student import Student
from src.domain.discipline import Discipline
from src.domain.grades import Grades
from unittest import TestCase


class GradesService:
    def __init__(self, grades_repository, student_repository, discipline_repository):
        self.grades_repository = grades_repository
        self.student_repository = student_repository
        self.discipline_repository = discipline_repository

    def add_grade(self, grade):
        self.grades_repository.add_grade(grade)

    def remove_student_grades(self, student_id):
        self.grades_repository.remove_student_grades(student_id)

    def remove_discipline_grades(self, discipline_id):
        self.grades_repository.remove_discipline_grades(discipline_id)


class TestGradesService(TestCase):
    def setUp(self):
        self.grades_repository = MemoryRepository()
        self.student_repository = MemoryRepository()
        self.discipline_repository = MemoryRepository()
        self.grades_service = GradesService(self.grades_repository, self.student_repository, self.discipline_repository)
        self.student1 = Student(101, "Alice")
        self.student2 = Student(102, "Bob")
        self.grades_repository.students = [self.student1, self.student2]
        self.discipline1 = Discipline(201, "Math")
        self.discipline2 = Discipline(202, "Computer Science")
        self.grade1 = Grades(202, 102, 9.0)
        self.grade2 = Grades(201, 101, 4.32)
        self.grades_repository.disciplines = [self.discipline1, self.discipline2]

    def test_add_grade(self):
        new_grade = Grades(201, 101, 9.0)
        result = self.grades_service.add_grade(new_grade)
        self.assertTrue(result)
        self.assertIn(new_grade, self.grades_repository.grades)

    def test_failing_add_grade(self):
        new_grade = Grades(1001, 101, 5.65)
        result = self.grades_service.add_grade(new_grade)
        self.assertFalse(result)
        self.assertNotIn(new_grade, self.grades_repository.grades)
