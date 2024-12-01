from src.domain.student import generate_students
from src.domain.discipline import generate_disciplines
from src.domain.grades import Grades
from src.domain.grades import generate_random_grades
from src.repository.MemoryRepository import MemoryRepository
from src.repository.TextFileRepository import TextFileRepository
from src.repository.BinaryFileRepository import BinaryFileRepository
from src.services.studentService import StudentService
from src.services.disciplineService import DisciplineService
from src.services.gradesService import GradesService
from src.repository.MemoryRepository import MenuError
import configparser
from src.services.undoService import *


def read_settings():
    config = configparser.ConfigParser()
    config.read("settings.properties")
    settings = {"repository": config.get("settings", "repository"),
                "students": config.get("settings", "students"),
                "disciplines": config.get("settings", "disciplines"),
                "grades": config.get("settings", "grades")}
    return settings


class UI:
    def __init__(self, students_service, discipline_service, grades_service):
        self.students_service = students_service
        self.discipline_service = discipline_service
        self.grades_service = grades_service
        self.undo_service = UndoRedoService(self.students_service, self.discipline_service, self.grades_service)
        self.__main_menu_entry = None
        self.__sub_menu_entry = None

    @staticmethod
    def print_main_menu():
        print("1. Add")
        print("2. Remove")
        print("3. Update name")
        print("4. List")
        print("5. Grade students")
        print("6. Search students")
        print("7. Search disciplines")
        print("8. Show failing students")
        print("9. Show students based on school situation")
        print("10. Show disciplines descending by student's average grade")
        print("11. Undo")
        print("12. Redo")
        print("0. Exit")

    @staticmethod
    def print_add_menu():
        print("1. Add student")
        print("2. Add discipline")
        print("0. Back")

    @staticmethod
    def print_remove_menu():
        print("1. Remove student")
        print("2. Remove discipline")
        print("0. Back")

    @staticmethod
    def print_update_menu():
        print("1. Update a student name")
        print("2. Update a discipline name")
        print("0. Back")

    @staticmethod
    def print_list_menu():
        print("1. Show all students")
        print("2. Show all disciplines")
        print("0. Back")

    def start(self):
        add_option = 1
        remove_option = 2
        update_option = 3
        list_option = 4
        grade_option = 5
        search_students_option = 6
        search_disciplines_option = 7
        show_failing_students_option = 8
        show_students_based_on_school_situation_option = 9
        show_disciplines_based_on_students_average_option = 10
        undo_option = 11
        redo_option = 12
        exit_option = 0
        valid_main_menu_options = [add_option, remove_option, update_option, list_option, grade_option, search_students_option, search_disciplines_option, show_failing_students_option, show_students_based_on_school_situation_option, show_disciplines_based_on_students_average_option, undo_option, redo_option, exit_option]
        while True:
            self.print_main_menu()
            try:
                self.__main_menu_entry = int(input("-> ").strip())
                if self.__main_menu_entry not in valid_main_menu_options:
                    raise MenuError("Please enter a correct option from the menu!")
                if self.__main_menu_entry == add_option:
                    add_student_option = 1
                    add_discipline_option = 2
                    back_option = 0
                    valid_sub_menu_options = [add_student_option, add_discipline_option, back_option]
                    while True:
                        self.print_add_menu()
                        try:
                            self.__sub_menu_entry = int(input("-> ").strip())
                            if self.__sub_menu_entry not in valid_sub_menu_options:
                                raise MenuError("Please enter a correct option from the menu!")
                            if self.__sub_menu_entry == add_student_option:
                                user_student_id_input = int(input("Enter the student's id: ").strip())
                                self.students_service.repository.check_id(user_student_id_input)
                                user_student_name_input = input("Enter the student's name: ").strip()
                                student_to_be_added = Student(user_student_id_input, user_student_name_input)
                                student_command = AddStudentCommand(self.students_service, student_to_be_added)
                                if self.students_service.add_student(student_to_be_added):
                                    print("Student added successfully!")
                                self.undo_service.execute_command(student_command)
                            elif self.__sub_menu_entry == add_discipline_option:
                                user_discipline_id_input = int(input("Enter the discipline's id: ").strip())
                                self.discipline_service.repository.check_id(user_discipline_id_input)
                                user_discipline_name_input = input("Enter the discipline's name: ").strip()
                                discipline_to_be_added = Discipline(user_discipline_id_input, user_discipline_name_input)
                                discipline_command = AddDisciplineCommand(self.discipline_service, discipline_to_be_added)
                                if self.discipline_service.add_discipline(discipline_to_be_added):
                                    print("Discipline added successfully!")
                                self.undo_service.execute_command(discipline_command)
                            else:
                                break
                        except (MenuError, ValueError, RepositoryError) as error:
                            print(error)
                elif self.__main_menu_entry == remove_option:
                    remove_student_option = 1
                    remove_discipline_option = 2
                    back_option = 0
                    valid_sub_menu_options = [remove_student_option, remove_discipline_option, back_option]
                    while True:
                        self.print_remove_menu()
                        try:
                            self.__sub_menu_entry = int(input("-> ").strip())
                            if self.__sub_menu_entry not in valid_sub_menu_options:
                                raise MenuError("Please enter a correct option from the menu!")
                            if self.__sub_menu_entry == remove_student_option:
                                user_student_id_input = int(input("Enter the student's id: ").strip())
                                self.students_service.repository.check_id(user_student_id_input)
                                for student in self.students_service.repository.students:
                                    if student.student_id == user_student_id_input:
                                        student = Student(user_student_id_input, student.name)
                                student_command = RemoveStudentCommand(self.students_service, self.grades_service, student)
                                if self.students_service.remove_student(user_student_id_input):
                                    print("Student removed successfully!")
                                self.undo_service.execute_command(student_command)
                            elif self.__sub_menu_entry == remove_discipline_option:
                                user_discipline_id_input = int(input("Enter the discipline's id: ").strip())
                                self.discipline_service.repository.check_id(user_discipline_id_input)
                                for discipline in self.discipline_service.repository.disciplines:
                                    if discipline.discipline_id == user_discipline_id_input:
                                        discipline = Discipline(user_discipline_id_input, discipline.name)
                                discipline_command = RemoveDisciplineCommand(self.discipline_service, self.grades_service, discipline)
                                if self.discipline_service.remove_discipline(user_discipline_id_input):
                                    print("Discipline removed successfully!")
                                self.undo_service.execute_command(discipline_command)
                            else:
                                break
                        except (RepositoryError, MenuError, ValueError) as error:
                            print(error)
                elif self.__main_menu_entry == update_option:
                    update_student_option = 1
                    update_discipline_option = 2
                    back_option = 0
                    valid_sub_menu_options = [update_student_option, update_discipline_option, back_option]
                    while True:
                        self.print_update_menu()
                        try:
                            self.__sub_menu_entry = int(input("-> ").strip())
                            if self.__sub_menu_entry not in valid_sub_menu_options:
                                raise MenuError("Please enter a correct option from the menu!")
                            if self.__sub_menu_entry == update_student_option:
                                user_student_id_input = int(input("Enter the student's id: ").strip())
                                self.students_service.repository.check_id(user_student_id_input)
                                user_student_new_name_input = input("Enter the student's new name: ").strip()
                                for student in self.students_service.repository.students:
                                    if student.student_id == user_student_id_input:
                                        student = Student(user_student_id_input, student.name)
                                student_command = UpdateStudentCommand(self.students_service, student, user_student_new_name_input)
                                if self.students_service.repository.update_student(user_student_id_input, user_student_new_name_input):
                                    print("Student updated!")
                                self.undo_service.execute_command(student_command)
                            elif self.__sub_menu_entry == update_discipline_option:
                                user_discipline_id_input = int(input("Enter the discipline's id: ").strip())
                                self.discipline_service.repository.check_id(user_discipline_id_input)
                                user_discipline_new_name_input = input("Enter the discipline's new name: ").strip()
                                for discipline in self.discipline_service.repository.disciplines:
                                    if discipline.discipline_id == user_discipline_id_input:
                                        discipline = Discipline(user_discipline_id_input, discipline.name)
                                discipline_command = UpdateDisciplineCommand(self.discipline_service, discipline, user_discipline_new_name_input)
                                if self.discipline_service.repository.update_discipline(user_discipline_id_input, user_discipline_new_name_input):
                                    print("Discipline updated!")
                                self.undo_service.execute_command(discipline_command)
                            else:
                                break
                        except (MenuError, ValueError, RepositoryError) as error:
                            print(error)
                elif self.__main_menu_entry == list_option:
                    show_all_students_option = 1
                    show_all_disciplines_option = 2
                    back_option = 0
                    valid_sub_menu_options = [show_all_students_option, show_all_disciplines_option, back_option]
                    while True:
                        self.print_list_menu()
                        try:
                            self.__sub_menu_entry = int(input("-> ").strip())
                            if self.__sub_menu_entry not in valid_sub_menu_options:
                                raise MenuError("Please enter a correct option from the menu!")
                            if self.__sub_menu_entry == show_all_students_option:
                                all_students = self.students_service.all
                                for student in all_students:
                                    print(student)
                            elif self.__sub_menu_entry == show_all_disciplines_option:
                                all_disciplines = self.discipline_service.all
                                for discipline in all_disciplines:
                                    print(discipline)
                            else:
                                break
                        except (RepositoryError, MenuError, ValueError) as error:
                            print(error)
                elif self.__main_menu_entry == grade_option:
                    try:
                        user_student_id_input = int(input("Enter the student's id: ").strip())
                        self.students_service.repository.check_id(user_student_id_input)
                        user_discipline_id_input = int(input("Enter the discipline's id: ").strip())
                        self.discipline_service.repository.check_id(user_discipline_id_input)
                        user_grade_value_input = float(input("Enter the grade: ").strip())
                        self.students_service.repository.check_grade_value(user_grade_value_input)
                        new_grade = Grades(user_discipline_id_input, user_student_id_input, user_grade_value_input)
                        if self.grades_service.add_grade(new_grade):
                            print("Grade successfully added!")
                    except (RepositoryError, ValueError) as error:
                        print(error)
                elif self.__main_menu_entry == search_students_option:
                    user_query = input("Please enter the search query: ").strip()
                    if user_query == "":
                        print("Please insert a non-empty search query next time!")
                    else:
                        query_students = self.students_service.search_students(user_query)
                        if isinstance(query_students, RepositoryError):
                            print(query_students)
                        else:
                            for student in query_students:
                                print(student)
                elif self.__main_menu_entry == search_disciplines_option:
                    user_query = input("Please enter the search query: ").strip()
                    if user_query == "":
                        print("Please insert a non-empty search query next time!")
                    else:
                        query_disciplines = self.discipline_service.search_disciplines(user_query)
                        if isinstance(query_disciplines, RepositoryError):
                            print(query_disciplines)
                        else:
                            for discipline in query_disciplines:
                                print(discipline)
                elif self.__main_menu_entry == show_failing_students_option:
                    failing_students = self.students_service.failing
                    for student in failing_students:
                        print(student)
                elif self.__main_menu_entry == show_students_based_on_school_situation_option:
                    sorted_students = self.students_service.sorted_students
                    for student in sorted_students:
                        print(student)
                elif self.__main_menu_entry == show_disciplines_based_on_students_average_option:
                    discipline_descending_grades = self.discipline_service.descending
                    for discipline in discipline_descending_grades:
                        print(discipline)
                elif self.__main_menu_entry == undo_option:
                    self.undo_service.undo()
                elif self.__main_menu_entry == redo_option:
                    self.undo_service.redo()
                else:
                    break
            except (MenuError, ValueError, RepositoryError) as error:
                print(error)


def main():
    try:
        number_of_procedural_generations = 20
        settings = read_settings()
        repository_type = settings["repository"]
        students_file = settings["students"]
        disciplines_file = settings["disciplines"]
        grades_file = settings["grades"]
        if repository_type == "inmemory":
            data = MemoryRepository()
        elif repository_type == "textfiles":
            data = TextFileRepository()
            data.set_students_file_name(students_file)
            data.set_disciplines_file_name(disciplines_file)
            data.set_grades_file_name(grades_file)
        elif repository_type == "binaryfiles":
            data = BinaryFileRepository()
            data.set_students_file_name(students_file)
            data.set_disciplines_file_name(disciplines_file)
            data.set_grades_file_name(grades_file)
        else:
            print("Invalid repository type!")
            return
        student_data = StudentService(data)
        discipline_data = DisciplineService(data)
        grades_data = GradesService(data)
        if not data.students:
            generate_students(number_of_procedural_generations, data)
        if not data.disciplines:
            generate_disciplines(number_of_procedural_generations, data)
        if not data.grades:
            generate_random_grades(number_of_procedural_generations, data)
        user = UI(student_data, discipline_data, grades_data)
        user.start()
    except FileNotFoundError as error:
        print(error)


if __name__ == "__main__":
    main()
