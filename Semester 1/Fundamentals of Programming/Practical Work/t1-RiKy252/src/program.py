#
# Functions section
#


def animal_list_representation(animal_code: str, animal_name: str, animal_type: str, animal_species: str):
    return [animal_code, animal_name, animal_type, animal_species]


def get_animal_code(animal: list):
    animal_code_index = 0
    return animal[animal_code_index]


def get_animal_name(animal: list):
    animal_name_index = 1
    return animal[animal_name_index]


def get_animal_type(animal: list):
    animal_type_index = 2
    return animal[animal_type_index]


def get_animal_species(animal: list):
    animal_species_index = 3
    return animal[animal_species_index]


def add_animal(animal_code: str, animal_name: str, animal_type: str, animal_species: str, animal_data: list):
    """
    Adds a new animal at the end of the animal data specified
    :param animal_code: the code of the new animal
    :param animal_name: the name of the new animal
    :param animal_type: the type of the new animal
    :param animal_species: the species of the new animal
    :param animal_data: the animal data to which we append the new animal
    :return: the new animal data
    """
    new_animal = animal_list_representation(animal_code, animal_name, animal_type, animal_species)
    animal_data.append(new_animal)
    return animal_data


def change_species_type(animal_species: str, new_type: str, animal_data: list):
    animal_species_index = 3
    animal_type_index = 2
    for animal in animal_data:
        if animal[animal_species_index] == animal_species:
            animal[animal_type_index] = new_type
    return animal_data


def sort_by_species(animal_data: list):
    animal_species_index = 3
    animal_data.sort(key=lambda animal: animal[animal_species_index])
    return animal_data


def sort_species_by_name(animal_data: list):
    for index in range(len(animal_data)):
        for j in range(index + 1, len(animal_data)):
            if animal_data[index][1] > animal_data[j][1]:
                aux = animal_data[index][1]
                animal_data[index][1] = animal_data[j][1]
                animal_data[j][1] = aux
    return animal_data


#
# User interface section
#


def add_animal_ui(animal_data: list):
    user_animal_code = input("Enter the code of the animal: ")
    if len(user_animal_code) == 0:
        raise ValueError("The code is not valid!")
    animal_code_index = 0
    for animal in animal_data:
        current_animal_code = animal[animal_code_index]
        if user_animal_code == current_animal_code:
            raise ValueError("The code is already used!")
    user_animal_name = input("Enter the name of the animal: ")
    if len(user_animal_name) == 0:
        raise ValueError("The name is not valid!")
    user_animal_type = input("Enter the type of the animal: ")
    if len(user_animal_type) == 0:
        raise ValueError("The type is not valid!")
    user_animal_species = input("Enter the species of the animal: ")
    if len(user_animal_species) == 0:
        raise ValueError("The species is not valid!")
    add_animal(user_animal_code, user_animal_name, user_animal_type, user_animal_species, animal_data)
    print("Animal added successfully!")
    return animal_data


def get_user_species():
    user_species = input("Enter the species: ")
    if len(user_species) == 0:
        raise ValueError("The species is not valid!")
    return user_species


def get_user_new_type():
    user_type = input("Enter the new type: ")
    if len(user_type) == 0:
        raise ValueError("The new type is not valid!")
    return user_type


def change_species_types_ui(animal_data: list):
    user_species = get_user_species()
    user_new_type = get_user_new_type()
    change_species_type(user_species, user_new_type, animal_data)


def print_menu():
    print("1. Add an animal")
    print("2. Change species type")
    print("3. Show animals sorted by species")
    print("0. Exit the program")


def start():
    add_animal_option = 1
    change_species_type_option = 2
    show_animals_sorted_by_species_option = 3
    exit_program_option = 0
    valid_menu_options = [add_animal_option, change_species_type_option, show_animals_sorted_by_species_option, exit_program_option]
    animal_data = [['Z01', 'Alex', 'herbivore', 'zebra'], ['Z02', 'David', 'herbivore', 'giraffe'], ['Z03', 'Oliver', 'carnivore', 'lion'], ['Z04', 'Thomas', 'carnivore', 'tiger'], ['Z05', 'Christian', 'bird', 'owl']]
    while True:
        try:
            print_menu()
            user_option = int(input("Enter an option from the menu: "))
            if user_option not in valid_menu_options:
                print("Please insert a valid option...")
            else:
                if user_option == add_animal_option:
                    add_animal_ui(animal_data)
                elif user_option == change_species_type_option:
                    change_species_types_ui(animal_data)
                elif user_option == show_animals_sorted_by_species_option:
                    sorted_by_species_animal_data = sort_by_species(animal_data)
                    print(sort_species_by_name(sorted_by_species_animal_data))
                else:
                    break
        except ValueError as value_error:
            print(value_error)


start()
