from domain import Assignment


class AssignmentRepository:
    def __init__(self):
        self.assignments = []
        id_index = 0
        name_index = 1
        solution_index = 2
        with open("assigment.txt", "r") as file:
            lines = file.readlines()
            for line in lines:
                content = line.strip().split(", ")
                new_assignment = Assignment(int(content[id_index]), content[name_index], content[solution_index])
                self.assignments.append(new_assignment)

    def save_assignments(self):
        """
        This method writes all the assignments to the input file
        """
        with open("assigment.txt", "w") as file:
            for assignment in self.assignments:
                file.write(str(assignment.assigment_id) + ", " + assignment.student_name + ", " + assignment.solution)
                file.write("\n")

    def check_unique_id(self, id_to_be_checked):
        """
        This method checks if an id already exists or not
        :return: true if the id doesn't exist
        Raises AssertionError if the id already exists
        """
        for assigment in self.assignments:
            if assigment.assigment_id == id_to_be_checked:
                raise AssertionError("The id is not unique!")
        return True

    @staticmethod
    def check_valid_student_name(student_name: str):
        """
        This static method checks if a given student name has at least 3 characters
        :return: true if it is valid
        Raises AssertionError if it's not valid
        """
        if len(student_name) >= 3:
            return True
        raise AssertionError("The student's name must contain at least 3 characters!")

    @staticmethod
    def check_valid_solution(solution: str):
        """
        This static method checks if a given solution is valid, so it is non-empty
        :return: true if it valid
        Raises AssertionError if it's not valid
        """
        if solution.strip() == "":
            raise AssertionError("The solution is empty!")
        return True

    def add_assignment(self, assignment_id, student_name, solution):
        """
        This method creates a new assignment with the given domain and adds it to the repository
        """
        new_assignment = Assignment(assignment_id, student_name, solution)
        self.assignments.append(new_assignment)
        self.save_assignments()

    def find_dishonest_pairs(self):
        assignment_id_index = 0
        assignment_solution_index = 1
        solutions_list = []
        pairs = []
        for assignment in self.assignments:
            solutions_list.append([assignment.assigment_id, assignment.solution.split(" ")])
        for i in range(len(solutions_list)):
            for j in range(i + 1, len(solutions_list)):
                common_words = 0
                i_word_counter = len(solutions_list[i][assignment_solution_index])
                j_word_counter = len(solutions_list[j][assignment_solution_index])
                for i_word in solutions_list[i][assignment_solution_index]:
                    if i_word in solutions_list[j][assignment_solution_index]:
                        common_words += 1
                if common_words == 0:
                    percentage = 0
                else:
                    if i_word_counter < j_word_counter:
                        percentage = common_words / i_word_counter
                    else:
                        percentage = common_words / j_word_counter
                if percentage >= 0.20:
                    percentage *= 100
                    percentage = str(percentage) + "%"
                    pairs.append([solutions_list[i][assignment_id_index], solutions_list[j][assignment_id_index], percentage])
        dishonest_pairs = ""
        first_pair_id_index = 0
        second_pair_id_index = 1
        percent_index = 2
        for pair in pairs:
            for assignment in self.assignments:
                if assignment.assigment_id == pair[first_pair_id_index] or assignment.assigment_id == pair[second_pair_id_index]:
                    student_name = assignment.student_name
                    dishonest_pairs += student_name
                    dishonest_pairs += " "
            dishonest_pairs += pair[percent_index]
            dishonest_pairs += "\n"
        if dishonest_pairs == "":
            return "There are no dishonest pairs!"
        return dishonest_pairs

    def all_assignments(self):
        assignments_message = ""
        for assignment in self.assignments:
            assignments_message += assignment.__str__()
            assignments_message += "\n"
        return assignments_message
