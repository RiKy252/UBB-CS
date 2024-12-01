from src.repository.MemoryRepository import RepositoryError
from src.repository.MemoryRepository import MemoryRepository
from src.domain.student import Student
from unittest import TestCase


class StudentService:
    def __init__(self, repository):
        self.repository = repository

    def add_student(self, student):
        self.repository.add_student(student)

    def remove_student(self, student_id):
        self.repository.remove_student(student_id)

    def update_student(self, student_id, new_student_name):
        self.repository.update_student(student_id, new_student_name)

    def search_students(self, user_query):
        return self.repository.search_students(user_query)

    @property
    def all(self):
        return self.repository.all_students

    @property
    def failing(self):
        return self.repository.failing_students

    @property
    def sorted_students(self):
        return self.repository.sorted_students


class TestStudentService(TestCase):
    def setUp(self):
        self.repository = MemoryRepository()
        self.service = StudentService(self.repository)
        self.student1 = Student(1, "Bob")
        self.student2 = Student(2, "Carl")
        self.student3 = Student(3, "Charlie")
        self.repository.students = [self.student1, self.student2, self.student3]

    def test_add_student(self):
        new_student = Student(10, "Alex")
        result = self.service.add_student(new_student)
        self.assertTrue(result)
        self.assertIn(new_student, self.repository.students)

    def test_failing_add_student(self):
        new_student = Student(1, "Michael")
        result = self.service.add_student(new_student)
        self.assertFalse(result)
        self.assertNotIn(new_student.name, self.repository.students)

    def test_remove_student(self):
        id_of_student_to_be_removed = 2
        result = self.service.remove_student(id_of_student_to_be_removed)
        self.assertTrue(result)
        self.assertNotIn(id_of_student_to_be_removed, self.repository.students)

    def test_failing_remove_student(self):
        id_of_student_to_be_removed = 101
        result = self.service.remove_student(id_of_student_to_be_removed)
        self.assertFalse(result)
        self.assertNotIn(id_of_student_to_be_removed, self.repository.students)

    def test_update_student(self):
        id_of_student_to_be_updated = 3
        new_student_name = "Charles"
        expected_student = Student(3, "Charles")
        result = self.service.update_student(id_of_student_to_be_updated, new_student_name)
        self.assertTrue(result)
        self.assertIn(expected_student, self.repository.students)

    def test_failing_update_student(self):
        id_of_student_to_be_updated = 404
        new_student_name = "Johnny"
        expected_student = Student(404, "Johnny")
        result = self.service.update_student(id_of_student_to_be_updated, new_student_name)
        self.assertFalse(result)
        self.assertNotIn(expected_student, self.repository.students)

    def test_search_students(self):
        search_query = "ArL"
        result = self.service.search_students(search_query)
        self.assertEqual(result, [self.student2, self.student3])

    def test_failing_search_students(self):
        search_query = "M"
        result = self.service.search_students(search_query)
        self.assertIsInstance(result, RepositoryError)
        self.assertEqual(str(result), "No students found!")
