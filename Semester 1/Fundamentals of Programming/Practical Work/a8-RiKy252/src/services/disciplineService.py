from src.repository.MemoryRepository import RepositoryError
from unittest import TestCase
from src.repository.MemoryRepository import MemoryRepository
from src.domain.discipline import Discipline


class DisciplineService:
    def __init__(self, repository):
        self.repository = repository

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

    def test_add_discipline(self):
        new_discipline = Discipline(1, "Data science")
        result = self.service.add_discipline(new_discipline)
        self.assertTrue(result)
        self.assertIn(new_discipline, self.repository.disciplines)

    def test_failing_add_discipline(self):
        new_discipline = Discipline(101, "Data Science")
        result = self.service.add_discipline(new_discipline)
        self.assertFalse(result)
        self.assertNotIn(new_discipline.name, self.repository.disciplines)

    def test_remove_discipline(self):
        id_of_discipline_to_be_removed = 101
        result = self.service.remove_discipline(id_of_discipline_to_be_removed)
        self.assertTrue(result)
        self.assertNotIn(id_of_discipline_to_be_removed, self.repository.disciplines)

    def test_failing_remove_disciplines(self):
        id_of_discipline_to_be_removed = 404
        result = self.service.remove_discipline(id_of_discipline_to_be_removed)
        self.assertFalse(result)
        self.assertNotIn(id_of_discipline_to_be_removed, self.repository.disciplines)

    def test_update_discipline(self):
        id_of_discipline_to_be_updated = 101
        new_discipline_name = "Algebra"
        expected_discipline = Discipline(101, "Algebra")
        result = self.service.update_discipline(id_of_discipline_to_be_updated, new_discipline_name)
        self.assertTrue(result)
        self.assertIn(expected_discipline, self.repository.disciplines)

    def test_failing_update_discipline(self):
        id_of_discipline_to_be_updated = 404
        new_discipline_name = "Computer Science"
        expected_discipline = Discipline(404, "Computer Science")
        result = self.service.update_discipline(id_of_discipline_to_be_updated, new_discipline_name)
        self.assertFalse(result)
        self.assertNotIn(expected_discipline, self.repository.disciplines)

    def test_search_disciplines(self):
        search_query = "CH"
        result = self.service.search_disciplines(search_query)
        self.assertEqual(result, [self.discipline3])

    def test_failing_search_disciplines(self):
        search_query = "Geo"
        result = self.service.search_disciplines(search_query)
        self.assertIsInstance(result, RepositoryError)
        self.assertEqual(str(result), "No disciplines found!")
