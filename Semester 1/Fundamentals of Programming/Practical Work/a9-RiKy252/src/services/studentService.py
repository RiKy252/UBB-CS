class StudentService:
    def __init__(self, repository):
        self.repository = None
        self.select_repository(repository)

    def select_repository(self, repository):
        self.repository = repository

    def change_repository(self, repository):
        self.select_repository(repository)

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
