from unittest import TestCase


class Student:
    def __init__(self, student_id: int, name: str):
        self.__student_id = student_id
        self.__name = name

    @property
    def student_id(self):
        return self.__student_id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, new_name):
        self.__name = new_name

    def __str__(self):
        return "ID: " + str(self.student_id) + ", " + self.name

    def __eq__(self, other):
        if not isinstance(other, Student):
            return False
        return self.student_id == other.student_id


class TestStudent(TestCase):
    def test_student_id(self):
        student = Student(1001, "Josh")
        self.assertEqual(student.student_id, 1001)

    def test_student_name(self):
        student = Student(750, "Simon")
        self.assertEqual(student.name, "Simon")

    def test_set_student_name(self):
        student = Student(10, "Harry")
        student.name = "Ethan"
        self.assertEqual(student.name, "Ethan")

    def test_student_string(self):
        student = Student(1, "Oliver")
        self.assertEqual(student.__str__(), "ID: 1, Oliver")

    def test_student_equality(self):
        first_student = Student(1, "Alex")
        second_student = Student(1, "Lauren")
        self.assertEqual(first_student, second_student)


def generate_students(number_of_students: int):
    generated_students = []
    students_name_list = ["Alice", "Bob", "Charlie", "David", "Emma", "Frank", "Grace", "Henry", "Ivy", "Jack", "Katherine", "Liam", "Mia", "Noah", "Olivia", "Penelope", "Quinn", "Ryan", "Sophia", "Thomas"]
    starting_id = 1
    for index in range(number_of_students):
        student_id = starting_id + index
        student_name = students_name_list[index]
        generated_students.append(Student(student_id, student_name))

    return generated_students


def test_generate_students():
    first_student = Student(1, "Alice")
    second_student = Student(2, "Bob")
    assert generate_students(2) == [first_student, second_student]


test_generate_students()
