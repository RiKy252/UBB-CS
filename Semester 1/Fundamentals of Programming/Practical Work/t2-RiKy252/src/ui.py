from repository import AssignmentRepository
from services import AssigmentService


class UI:
    def __init__(self, service):
        self.service = service

    @staticmethod
    def print_menu():
        print("1. Add assignment")
        print("2. Display assignments")
        print("3. Dishonesty check")
        print("0. Exit")

    def start(self):
        add_assignment_option = 1
        display_assignments_option = 2
        dishonesty_option = 3
        exit_option = 0
        while True:
            try:
                self.print_menu()
                user_option = int(input("Select an option: "))
                if user_option == add_assignment_option:
                    user_assignment_id_input = int(input("Enter the assigment ID: "))
                    self.service.repository.check_unique_id(user_assignment_id_input)
                    user_student_name_input = input("Enter the student's name: ").strip()
                    self.service.repository.check_valid_student_name(user_student_name_input)
                    user_solution_input = input("Enter the assignment's solution: ").strip()
                    self.service.repository.check_valid_solution(user_solution_input)
                    self.service.add_assignment(user_assignment_id_input, user_student_name_input, user_solution_input)
                elif user_option == display_assignments_option:
                    print(self.service.all_assignments())
                elif user_option == dishonesty_option:
                    print(self.service.find_dishonest_pairs())
                elif user_option == exit_option:
                    break
                else:
                    print("Invalid menu option!")
            except (ValueError, AssertionError) as error:
                print(error)


def main():
    repo = AssignmentRepository()
    service = AssigmentService(repo)
    user = UI(service)
    user.start()


main()
