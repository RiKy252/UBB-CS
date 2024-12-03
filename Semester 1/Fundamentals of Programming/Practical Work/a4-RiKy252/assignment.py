"""
Backtracking problem statement:

10. A group of n (n<=10) persons, numbered from 1 to n are placed on a row of chairs,
but between every two neighbor persons
(e.g. persons 3 and 4, or persons 7 and 8) some conflicts appeared.
Display all the possible modalities to replace the persons, such that between any two
persons in conflict stay one or at most two other persons.

"""


def create_user_input_list() -> list:
    user_list = []
    while True:
        user_input = input("Enter an element (or 'q' to quit):")
        if user_input.lower() == 'q':
            break
        user_list.append(user_input)
    return user_list


def print_solution(solution: list):
    print(solution)


def no_consecutive_positions_with_difference_1(persons: list, number_of_persons: int) -> bool:
    if len(persons) == number_of_persons:
        for index in range(1, len(persons)):
            if abs(persons.index(index) - persons.index(index + 1)) > 3 or abs(persons.index(index) - persons.index(index + 1)) == 1:
                return False
        return True
    else:
        return False


def generate_persons_with_no_consecutive_positions_with_difference_1_recursive(number_of_persons: int, persons: list):
    if len(persons) == number_of_persons:
        if no_consecutive_positions_with_difference_1(persons, number_of_persons):
            print_solution(persons)
        return
    for index in range(1, number_of_persons + 1):
        persons.append(index)
        if len(persons) == len(set(persons)):
            generate_persons_with_no_consecutive_positions_with_difference_1_recursive(number_of_persons, persons)
        persons.pop()


def generate_persons_with_no_consecutive_positions_with_difference_1_iterative(number_of_persons: int):
    modality = [0]
    while modality:
        possible_solution = False
        while not possible_solution and modality[-1] < number_of_persons:
            modality[-1] = modality[-1] + 1
            possible_solution = len(set(modality)) == len(modality)  # no duplicates
        if possible_solution:
            if no_consecutive_positions_with_difference_1(modality, number_of_persons):
                print_solution(modality)
            modality.append(0)
        else:
            modality.pop()


"""

Dynamic programming problem statement

Given the set of positive integers S, partition this set into two subsets S1 and S2
so that the difference between the sum of the elements in S1 and S2 is minimal.
For example, for set S = { 1, 2, 3, 4, 5 }, the two subsets could be S1 = { 1, 2, 4 }
and S2 = { 3, 5 }. Display at least one of the solutions.

"""


def find_minimal_partitions_difference_naive(set_of_positive_integers):
    length_of_the_set = len(set_of_positive_integers)
    minimum_difference = float('inf')
    minimal_partition = []
    for binary_representation in range(2 ** length_of_the_set):
        subset_1 = []
        subset_2 = []
        for element_of_set in range(length_of_the_set):
            if (binary_representation >> element_of_set) & 1:
                subset_1.append(set_of_positive_integers[element_of_set])
            else:
                subset_2.append(set_of_positive_integers[element_of_set])
        sum_of_subset_1 = sum(subset_1)
        sum_of_subset_2 = sum(subset_2)
        current_subsets_difference = abs(sum_of_subset_1 - sum_of_subset_2)
        if current_subsets_difference < minimum_difference:
            minimum_difference = current_subsets_difference
            minimal_partition = [subset_1, subset_2]
    return minimal_partition


def can_we_form_with_first_i_elements_the_sum_j_boolean_matrix(set_of_positive_integers):
    number_of_elements = len(set_of_positive_integers)
    total_sum = sum(set_of_positive_integers)
    is_it_possible_to_form_current_sum_j_with_first_i_elements = [[False for _ in range(total_sum // 2 + 1)] for _ in range(number_of_elements + 1)]
    is_it_possible_to_form_current_sum_j_with_first_i_elements[0][0] = True

    for first_elements in range(1, number_of_elements + 1):
        for current_sum in range(total_sum // 2 + 1):
            is_it_possible_to_form_current_sum_j_with_first_i_elements[first_elements][current_sum] = is_it_possible_to_form_current_sum_j_with_first_i_elements[first_elements - 1][current_sum]
            if set_of_positive_integers[first_elements - 1] <= current_sum:
                is_it_possible_to_form_current_sum_j_with_first_i_elements[first_elements][current_sum] = is_it_possible_to_form_current_sum_j_with_first_i_elements[first_elements][current_sum] or is_it_possible_to_form_current_sum_j_with_first_i_elements[first_elements - 1][current_sum - set_of_positive_integers[first_elements - 1]]
    return is_it_possible_to_form_current_sum_j_with_first_i_elements


def find_minimal_partitions_difference_optimised(set_of_positive_integers):
    total_sum = sum(set_of_positive_integers)
    number_of_elements = len(set_of_positive_integers)

    is_it_possible_to_form_current_sum_j_with_first_i_elements = can_we_form_with_first_i_elements_the_sum_j_boolean_matrix(set_of_positive_integers)

    target_sum = 0
    for current_sum in range(total_sum // 2, -1, -1):
        if is_it_possible_to_form_current_sum_j_with_first_i_elements[number_of_elements][current_sum]:
            target_sum = current_sum
            break

    partition_1 = []
    partition_2 = []

    current_sum = target_sum
    while number_of_elements > 0 and current_sum > 0:
        if not is_it_possible_to_form_current_sum_j_with_first_i_elements[number_of_elements - 1][current_sum]:
            partition_1.append(set_of_positive_integers[number_of_elements - 1])
            current_sum -= set_of_positive_integers[number_of_elements - 1]
        else:
            partition_2.append(set_of_positive_integers[number_of_elements - 1])
        number_of_elements -= 1

    while number_of_elements > 0:
        partition_2.append(set_of_positive_integers[number_of_elements - 1])
        number_of_elements -= 1

    return partition_1, partition_2

# print("Recursive:")
# generate_persons_with_no_consecutive_positions_with_difference_1_recursive(5, [])
# print("Iterative:")
# generate_persons_with_no_consecutive_positions_with_difference_1_iterative(5)


print("Naive implementation: ")
print(find_minimal_partitions_difference_naive([1, 2, 3, 4, 5]))
print("Optimised implementation: ")
print(find_minimal_partitions_difference_optimised([1, 2, 3, 4, 5]))
print("The data structure used for optimisation: " + str(can_we_form_with_first_i_elements_the_sum_j_boolean_matrix([1, 2, 3, 4, 5])))
