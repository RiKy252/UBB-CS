from unittest import TestCase


class Discipline:
    def __init__(self, discipline_id: int, name: str):
        self.__discipline_id = discipline_id
        self.__name = name

    @property
    def discipline_id(self):
        return self.__discipline_id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, new_name):
        self.__name = new_name

    def __str__(self):
        return "ID: " + str(self.discipline_id) + ", " + self.name

    def __eq__(self, other):
        if not isinstance(other, Discipline):
            return False
        return self.discipline_id == other.discipline_id


class TestDiscipline(TestCase):
    def test_discipline_id(self):
        discipline = Discipline(1001, "Computer arhitecture")
        self.assertEqual(discipline.discipline_id, 1001)

    def test_discipline_name(self):
        discipline = Discipline(750, "Mathematical Analysis")
        self.assertEqual(discipline.name, "Mathematical Analysis")

    def test_set_discipline_name(self):
        discipline = Discipline(10, "FP")
        discipline.name = "Fundamentals of programming"
        self.assertEqual(discipline.name, "Fundamentals of programming")

    def test_discipline_string(self):
        discipline = Discipline(1, "Algebra")
        self.assertEqual(discipline.__str__(), "ID: 1, Algebra")

    def test_discipline_equality(self):
        first_discipline = Discipline(1, "CSA")
        second_discipline = Discipline(1, "Computer System Arhitecture")
        self.assertEqual(first_discipline, second_discipline)


def generate_disciplines(number_of_disciplines: int, data):
    disciplines_name_list = ["Artificial Intelligence", "Data Science", "Machine Learning", "Computer Networks", "Software Engineering", "Database Management", "Cybersecurity", "Human-Computer Interaction", "Computer Graphics", "Algorithms and Data Structures", "Computer Vision", "Operating Systems", "Information Systems", "Robotics", "Natural Language Processing", "Cloud Computing", "Computer Architecture", "Web Development", "Mobile App Development", "Parallel Computing"]
    starting_id = 1
    for index in range(number_of_disciplines):
        discipline_id = starting_id + index
        discipline_name = disciplines_name_list[index]
        data.add_discipline(Discipline(discipline_id, discipline_name))
