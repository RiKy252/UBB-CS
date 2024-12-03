class GradesService:
    def __init__(self, repository):
        self.repository = None
        self.select_repository(repository)

    def select_repository(self, repository):
        self.repository = repository

    def change_repository(self, repository):
        self.select_repository(repository)

    def add_grade(self, grade):
        self.repository.add_grade(grade)

    def remove_student_grades(self, student_id):
        self.repository.remove_student_grades(student_id)

    def remove_discipline_grades(self, discipline_id):
        self.repository.remove_discipline_grades(discipline_id)
