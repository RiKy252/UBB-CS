from src.repository.MemoryRepository import RepositoryError
from unittest import TestCase
from src.repository.MemoryRepository import MemoryRepository
from src.domain.discipline import Discipline


class DisciplineService:
    def __init__(self, repository):
        self.repository = None
        self.select_repository(repository)

    def select_repository(self, repository):
        self.repository = repository

    def change_repository(self, repository):
        self.select_repository(repository)

    def add_discipline(self, discipline):
        self.repository.add_discipline(discipline)

    def remove_discipline(self, discipline_id):
        self.repository.remove_discipline(discipline_id)

    def update_discipline(self, discipline_id, new_discipline_name):
        self.repository.update_discipline(discipline_id, new_discipline_name)

    def search_disciplines(self, user_query):
        return self.repository.search_disciplines(user_query)

    @property
    def all(self):
        return self.repository.all_disciplines

    @property
    def descending(self):
        return self.repository.sorted_disciplines


class TestDisciplineService(TestCase):
    def setUp(self):
        self.repository = MemoryRepository()
        self.service = DisciplineService(self.repository)
        self.discipline1 = Discipline(101, "Analysis")
        self.discipline2 = Discipline(102, "Computer Science")
        self.discipline3 = Discipline(103, "Machine Learning")
        self.repository.disciplines = [self.discipline1, self.discipline2, self.discipline3]
