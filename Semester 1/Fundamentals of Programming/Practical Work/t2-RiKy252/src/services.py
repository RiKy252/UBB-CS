class AssigmentService:
    def __init__(self, repository):
        self.repository = repository

    def add_assignment(self, assignment_id, student_name, solution):
        """
        This method creates a new assignment with the given domain and adds it to the repository
        """
        self.repository.add_assignment(assignment_id, student_name, solution)

    def all_assignments(self):
        return self.repository.all_assignments()

    def find_dishonest_pairs(self):
        return self.repository.find_dishonest_pairs()
