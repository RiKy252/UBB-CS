from unittest import TestCase
from src.domain.student import TestStudent, test_generate_students
from src.domain.discipline import TestDiscipline, test_generate_disciplines
from src.domain.grades import TestGrade, test_generate_random_grades
from src.domain.student import Student
from src.domain.discipline import Discipline
from src.domain.grades import Grades


class RepositoryError(Exception):
    def __init__(self, message):
        self._message = message

    @property
    def message(self):
        return self._message

    def __str__(self):
        return self.message


class MemoryRepository:
    def __init__(self):
        self.students = []
        self.disciplines = []
        self.grades = []

    @staticmethod
    def check_id(user_id):
        if not isinstance(user_id, int):
            raise RepositoryError("The student's id must be an integer!")
        return True

    @staticmethod
    def check_grade_value(grade_value):
        if not isinstance(grade_value, float):
            raise RepositoryError("The grade value must be a number!")
        if grade_value < 0:
            raise RepositoryError("The grade value must be between 1-10!")
        if grade_value > 10:
            raise RepositoryError("The grade value must be between 1-10!")
        return True

    def check_student_exist(self, user_student_id):
        student_exists = False
        for current_student in self.students:
            current_student_id = current_student.student_id
            if current_student_id == user_student_id:
                student_exists = True
                break
        if not student_exists:
            raise RepositoryError("Student doesn't exist.")
        return student_exists

    def check_discipline_exist(self, user_discipline_id):
        discipline_exists = False
        for current_discipline in self.disciplines:
            current_discipline_id = current_discipline.discipline_id
            if current_discipline_id == user_discipline_id:
                discipline_exists = True
                break
        if not discipline_exists:
            raise RepositoryError("Discipline doesn't exist.")
        return discipline_exists

    def add_student(self, student):
        """
        This method adds a student in the current repository
        :param student: student to be added
        Raises RepositoryError if the student already exists
        """
        if student in self.students:
            raise RepositoryError("Student already exists.")
        else:
            self.students.append(student)

    def add_discipline(self, discipline):
        """
        This method adds a discipline in the current repository
        :param discipline: discipline to be added
        Raises RepositoryError if the discipline already exists
        """
        if discipline in self.disciplines:
            raise RepositoryError("Discipline already exists.")
        else:
            self.disciplines.append(discipline)

    def remove_student(self, student_id):
        """
        This method removes a student from the current repository
        :param student_id: the id of the student to be removed
        :return: None
        Raises RepositoryError if the id of the student isn't in the repository
        """
        for student in self.students:
            current_student_id = student.student_id
            if current_student_id == student_id:
                self.remove_student_grades(student_id)
                return self.students.remove(student)
        raise RepositoryError("Student doesn't exist.")

    def remove_discipline(self, discipline_id):
        """
        This method removes a discipline from the current repository
        :param discipline_id: the id of the discipline to be removed
        :return: None
        Raises RepositoryError if the id of the discipline isn't in the repository
        """
        for discipline in self.disciplines:
            current_discipline_id = discipline.discipline_id
            if current_discipline_id == discipline_id:
                self.remove_discipline_grades(discipline_id)
                return self.disciplines.remove(discipline)
        raise RepositoryError("Discipline doesn't exist.")

    def update_student(self, student_id, new_student_name):
        """
        This method updates a student from the repository, changing his name
        :param student_id: the id of the student to be updated
        :param new_student_name: the new student name after updating
        :return: the updated student
        Raises RepositoryError if the id of the student isn't in the repository
        """
        for student in self.students:
            current_student_id = student.student_id
            if current_student_id == student_id:
                student.name = new_student_name
                return student
        raise RepositoryError("Student doesn't exist.")

    def update_discipline(self, discipline_id, new_discipline_name):
        """
        This method updates a discipline from the repository, changing its name
        :param discipline_id: the id of the discipline to be updated
        :param new_discipline_name: the new discipline name after updating
        :return: the updated discipline
        Raises RepositoryError if the id of the discipline isn't in the repository
        """
        for discipline in self.disciplines:
            current_discipline_id = discipline.discipline_id
            if current_discipline_id == discipline_id:
                discipline.name = new_discipline_name
                return discipline
        raise RepositoryError("Discipline doesn't exist.")

    def add_grade(self, grade):
        self.check_student_exist(grade.student_id)
        self.check_discipline_exist(grade.discipline_id)
        self.grades.append(grade)

    def remove_student_grades(self, user_student_id):
        self.grades = [grade for grade in self.grades if grade.student_id != user_student_id]

    def remove_discipline_grades(self, user_discipline_id):
        self.grades = [grade for grade in self.grades if grade.discipline_id != user_discipline_id]

    def search_students(self, user_query):
        resulted_students = []
        user_query = user_query.lower()
        for student in self.students:
            student_name = student.name.lower()
            student_id = str(student.student_id)
            if user_query in student_name:
                resulted_students.append(student)
            elif user_query in student_id:
                resulted_students.append(student)
        if not resulted_students:
            raise RepositoryError("No students found!")
        return resulted_students

    def search_disciplines(self, user_query):
        resulted_disciplines = []
        user_query = user_query.lower()
        for discipline in self.disciplines:
            discipline_name = discipline.name.lower()
            discipline_id = str(discipline.discipline_id)
            if user_query in discipline_name:
                resulted_disciplines.append(discipline)
            elif user_query in discipline_id:
                resulted_disciplines.append(discipline)
        if not resulted_disciplines:
            raise RepositoryError("No disciplines found!")
        return resulted_disciplines

    def average_student_grade_for_discipline(self, user_student_id, user_discipline_id):
        sum_of_grades = 0
        number_of_grades = 0
        for grade in self.grades:
            if grade.student_id == user_student_id and grade.discipline_id == user_discipline_id:
                sum_of_grades += grade.grade_value
                number_of_grades += 1
        if number_of_grades == 0:
            raise RepositoryError("The student doesn't have any grades for this discipline!")
        average_grade = round(sum_of_grades / number_of_grades, 2)
        return average_grade

    def average_discipline_grade(self, user_discipline_id):
        sum_of_grades = 0
        number_of_grades = 0
        for grade in self.grades:
            if grade.discipline_id == user_discipline_id:
                sum_of_grades += grade.grade_value
                number_of_grades += 1
        if number_of_grades == 0:
            raise RepositoryError("The discipline doesn't have any grades!")
        average_grade = round(sum_of_grades / number_of_grades, 2)
        return average_grade

    def student_aggregated_average(self, user_student_id):
        average_grade = 0
        number_of_average_grades = 0
        for discipline in self.disciplines:
            try:
                average_grade += self.average_student_grade_for_discipline(user_student_id, discipline.discipline_id)
                number_of_average_grades += 1
            except RepositoryError:
                pass
        if number_of_average_grades == 0:
            raise RepositoryError("The student doesn't have any grades at all!")
        aggregate_average = round(average_grade / number_of_average_grades, 2)
        return aggregate_average

    @property
    def failing_students(self):
        failing_students = []
        if not self.students:
            return "The student repository is empty!"
        for student in self.students:
            for discipline in self.disciplines:
                try:
                    average_for_current_discipline = self.average_student_grade_for_discipline(student.student_id, discipline.discipline_id)
                    if average_for_current_discipline < 5:
                        failing_students.append(student)
                        break
                except RepositoryError:
                    pass
        if not failing_students:
            return "There are no failing students!"
        return failing_students

    @property
    def all_students(self):
        """
        This property returns a string with all the students, separated by end lines, or it returns a string specifying that the student repository is empty, if it is the case
        """
        all_students = []
        if not self.students:
            return "The student repository is empty!"
        for student in self.students:
            all_students.append(student)
        return all_students

    @property
    def all_disciplines(self):
        """
        This property returns a string with all the disciplines, separated by end lines, or it returns a string specifying that the discipline repository is empty, if it is the case
        """
        all_disciplines = []
        if not self.disciplines:
            return "The discipline repository is empty!"
        for discipline in self.disciplines:
            all_disciplines.append(discipline)
        return all_disciplines

    @property
    def sorted_students(self):
        sorted_students = []
        aggregated_average_student_list = []
        if not self.students:
            return "The student repository is empty!"
        for student in self.students:
            try:
                current_student_aggregated_average = self.student_aggregated_average(student.student_id)
                data_to_append = {"student": student, "aggregated_average": current_student_aggregated_average}
                aggregated_average_student_list.append(data_to_append)
            except RepositoryError:
                pass
        sorted_aggregated_average_list = sorted(aggregated_average_student_list, key=lambda value: value["aggregated_average"], reverse=True)
        for entry in sorted_aggregated_average_list:
            sorted_students.append(entry["student"])
        if not sorted_students:
            return "There are no grades at all!"
        return sorted_students

    @property
    def sorted_disciplines(self):
        sorted_disciplines = []
        average_discipline_grades_list = []
        if not self.disciplines:
            return "The discipline repository is empty!"
        for discipline in self.disciplines:
            try:
                current_discipline_average = self.average_discipline_grade(discipline.discipline_id)
                data_to_append = {"discipline": discipline, "discipline_average": current_discipline_average}
                average_discipline_grades_list.append(data_to_append)
            except RepositoryError:
                pass
        sorted_average_discipline_grades_list = sorted(average_discipline_grades_list, key=lambda value: value["discipline_average"], reverse=True)
        for entry in sorted_average_discipline_grades_list:
            sorted_disciplines.append(entry["discipline"])
        if not sorted_disciplines:
            return "There are no grades at all!"
        return sorted_disciplines


class TestRepositoryError(TestCase):
    def test_repository_error_message(self):
        repository_error = RepositoryError("This is a repository error!")
        self.assertEqual(repository_error.message, "This is a repository error!")

    def test_repository_error_string(self):
        repository_error = RepositoryError("This is a repository error!")
        self.assertEqual(repository_error.__str__(), "This is a repository error!")


class TestMemoryRepository(TestCase):

    def setUp(self):
        self.repository = MemoryRepository()
        self.student1 = Student(1, "Bob")
        self.student2 = Student(2, "Carl")
        self.student3 = Student(3, "Charlie")
        self.discipline1 = Discipline(101, "Data science")
        self.discipline2 = Discipline(102, "Computer arhitecture")
        self.discipline3 = Discipline(103, "Machine learning")
        self.grade1 = Grades(101, 1, 10.0)
        self.grade2 = Grades(102, 2, 4.50)
        self.grade3 = Grades(103, 3, 7.77)
        self.repository.students = [self.student1, self.student2, self.student3]
        self.repository.disciplines = [self.discipline1, self.discipline2, self.discipline3]
        self.repository.grades = [self.grade1, self.grade2, self.grade3]

    def test_check_id(self):
        user_id = 123
        result = MemoryRepository.check_id(user_id)
        self.assertTrue(result)

    def test_check_id_invalid(self):
        with self.assertRaises(RepositoryError) as error:
            MemoryRepository.check_id("123")
        self.assertEqual(str(error.exception), "The student's id must be an integer!")

    def test_check_grade_value(self):
        user_grade_value = 5.87
        result = MemoryRepository.check_grade_value(user_grade_value)
        self.assertTrue(result)

    def test_check_grade_value_invalid_type(self):
        with self.assertRaises(RepositoryError) as error:
            MemoryRepository.check_grade_value("not a float")
        self.assertEqual(str(error.exception), "The grade value must be a number!")

    def test_check_grade_high_value(self):
        with self.assertRaises(RepositoryError) as error:
            MemoryRepository.check_grade_value(11.0)
        self.assertEqual(str(error.exception), "The grade value must be between 1-10!")

    def test_check_grade_low_value(self):
        with self.assertRaises(RepositoryError) as error:
            MemoryRepository.check_grade_value(-1.0)
        self.assertEqual(str(error.exception), "The grade value must be between 1-10!")

    def test_check_student_exist(self):
        result = self.repository.check_student_exist(2)
        self.assertTrue(result)

    def test_check_student_does_not_exist(self):
        with self.assertRaises(RepositoryError) as error:
            self.repository.check_student_exist(1001)
        self.assertEqual(str(error.exception), "Student doesn't exist.")

    def test_check_discipline_exist(self):
        result = self.repository.check_discipline_exist(103)
        self.assertTrue(result)

    def test_check_discipline_does_not_exist(self):
        with self.assertRaises(RepositoryError) as error:
            self.repository.check_discipline_exist(404)
        self.assertEqual(str(error.exception), "Discipline doesn't exist.")

    def test_add_student(self):
        new_student = Student(10, "Alex")
        self.repository.add_student(new_student)
        self.assertIn(new_student, self.repository.students)

    def test_add_student_invalid(self):
        new_student = Student(1, "Robert")
        with self.assertRaises(RepositoryError) as error:
            self.repository.add_student(new_student)
        self.assertEqual(str(error.exception), "Student already exists.")

    def test_add_discipline_invalid(self):
        new_discipline = Discipline(101, "Analysis")
        with self.assertRaises(RepositoryError) as error:
            self.repository.add_discipline(new_discipline)
        self.assertEqual(str(error.exception), "Discipline already exists.")

    def test_add_discipline(self):
        new_discipline = Discipline(1, "Algebra")
        self.repository.add_discipline(new_discipline)
        self.assertIn(new_discipline, self.repository.disciplines)

    def test_remove_student(self):
        id_of_student_to_be_removed = 1
        self.repository.remove_student(id_of_student_to_be_removed)
        self.assertNotIn(id_of_student_to_be_removed, self.repository.students)

    def test_remove_student_invalid(self):
        id_of_student_to_be_removed = 404
        with self.assertRaises(RepositoryError) as error:
            self.repository.remove_student(id_of_student_to_be_removed)
        self.assertEqual(str(error.exception), "Student doesn't exist.")

    def test_remove_discipline(self):
        id_of_discipline_to_be_removed = 102
        self.repository.remove_discipline(id_of_discipline_to_be_removed)
        self.assertNotIn(id_of_discipline_to_be_removed, self.repository.disciplines)

    def test_remove_discipline_invalid(self):
        id_of_discipline_to_be_removed = 404
        with self.assertRaises(RepositoryError) as error:
            self.repository.remove_discipline(id_of_discipline_to_be_removed)
        self.assertEqual(str(error.exception), "Discipline doesn't exist.")

    def test_update_student(self):
        id_of_student_to_be_updated = 3
        new_student_name = "Jeremy"
        expected_student = Student(3, "Jeremy")
        self.repository.update_student(id_of_student_to_be_updated, new_student_name)
        self.assertIn(expected_student, self.repository.students)

    def test_update_discipline(self):
        id_of_discipline_to_be_updated = 102
        new_discipline_name = "OOP"
        expected_discipline = Discipline(102, "OOP")
        self.repository.update_discipline(id_of_discipline_to_be_updated, new_discipline_name)
        self.assertIn(expected_discipline, self.repository.disciplines)

    def test_add_grade(self):
        new_grade = Grades(102, 2, 9.80)
        self.repository.add_grade(new_grade)
        self.assertIn(new_grade, self.repository.grades)

    def test_search_students(self):
        search_query = "arl"
        result = self.repository.search_students(search_query)
        self.assertEqual(result, [self.student2, self.student3])

    def test_search_disciplines(self):
        search_query = "science"
        result = self.repository.search_disciplines(search_query)
        self.assertEqual(result, [self.discipline1])

    def test_average_student_grade_for_discipline(self):
        student_id = 2
        discipline_id = 102
        result = self.repository.average_student_grade_for_discipline(student_id, discipline_id)
        self.assertEqual(result, 4.50)

    def test_average_discipline_grade(self):
        discipline_id = 103
        result = self.repository.average_discipline_grade(discipline_id)
        self.assertEqual(result, 7.77)

    def test_student_aggregated_average(self):
        student_id = 1
        result = self.repository.student_aggregated_average(student_id)
        self.assertEqual(result, 10.0)

    def test_failing_students(self):
        result = self.repository.failing_students
        self.assertEqual(result, self.student2.__str__() + "\n")

    def test_all_students(self):
        result = self.repository.all_students
        self.assertEqual(result, self.student1.__str__() + "\n" + self.student2.__str__() + "\n" + self.student3.__str__() + "\n")

    def test_all_disciplines(self):
        result = self.repository.all_disciplines
        self.assertEqual(result, self.discipline1.__str__() + "\n" + self.discipline2.__str__() + "\n" + self.discipline3.__str__() + "\n")

    def test_sorted_students(self):
        result = self.repository.sorted_students
        self.assertEqual(result, self.student1.__str__() + "\n" + self.student3.__str__() + "\n" + self.student2.__str__() + "\n")

    def test_sorted_disciplines(self):
        result = self.repository.sorted_disciplines
        self.assertEqual(result, self.discipline1.__str__() + "\n" + self.discipline3.__str__() + "\n" + self.discipline2.__str__() + "\n")


execute_tests = TestStudent, TestDiscipline, TestGrade
test_generate_students()
test_generate_disciplines()
test_generate_random_grades()
