from texttable import Texttable
from random import randint


class Board:
    def __init__(self, size, apples):
        self.__size = size
        self.__data = [[" " for _ in range(size)] for _ in range(size)]
        self.__apples = apples
        middle = size // 2
        self.__data[middle][middle] = '+'
        self.__data[middle - 1][middle] = '*'
        self.__head_position_row = middle - 1
        self.__head_position_column = middle
        self.__snake_body = [[middle + 1, middle], [middle, middle], [self.__head_position_row, self.__head_position_column]]
        self.__data[middle + 1][middle] = '+'
        self.add_apples(apples)

    def add_apples(self, number_of_apples):
        apple_counter = 0
        while apple_counter < number_of_apples:
            random_row = randint(0, self.__size - 1)
            random_column = randint(0, self.__size - 1)
            if self.__data[random_row][random_column] == ' ':
                if random_row == 0 and 0 < random_column < self.__size - 1:
                    if self.__data[random_row + 1][random_column] != 'a' and self.__data[random_row][random_column - 1] != 'a' and self.__data[random_row][random_column + 1] != 'a':
                        self.__data[random_row][random_column] = 'a'
                        apple_counter += 1
                elif random_row == self.__size - 1 and 0 < random_column < self.__size - 1:
                    if self.__data[random_row - 1][random_column] != 'a' and self.__data[random_row][random_column - 1] != 'a' and self.__data[random_row][random_column + 1] != 'a':
                        self.__data[random_row][random_column] = 'a'
                        apple_counter += 1
                elif random_column == 0 and 0 < random_row < self.__size - 1:
                    if self.__data[random_row][random_column + 1] != 'a' and self.__data[random_row - 1][random_column] != 'a' and self.__data[random_row + 1][random_column] != 'a':
                        self.__data[random_row][random_column] = 'a'
                        apple_counter += 1
                elif random_column == self.__size - 1 and 0 < random_row < self.__size - 1:
                    if self.__data[random_row][random_column - 1] != 'a' and self.__data[random_row + 1][random_column] != 'a' and self.__data[random_row - 1][random_column] != 'a':
                        self.__data[random_row][random_column] = 'a'
                        apple_counter += 1
                elif random_row == 0 and random_column == 0:
                    if self.__data[random_row + 1][random_column] != 'a' and self.__data[random_row][random_column + 1] != 'a':
                        self.__data[random_row][random_column] = 'a'
                        apple_counter += 1
                elif random_row == 0 and random_column == self.__size - 1:
                    if self.__data[random_row + 1][random_column] != 'a' and self.__data[random_row][random_column - 1] != 'a':
                        self.__data[random_row][random_column] = 'a'
                        apple_counter += 1
                elif random_row == self.__size - 1 and random_column == 0:
                    if self.__data[random_row - 1][random_column] != 'a' and self.__data[random_row][random_column + 1] != 'a':
                        self.__data[random_row][random_column] = 'a'
                        apple_counter += 1
                elif random_row == self.__size - 1 and random_column == self.__size - 1:
                    if self.__data[random_row][random_column - 1] != 'a' and self.__data[random_row - 1][random_column] != 'a':
                        self.__data[random_row][random_column] = 'a'
                        apple_counter += 1
                elif self.__data[random_row - 1][random_column] != 'a' and self.__data[random_row + 1][random_column] != 'a' and self.__data[random_row][random_column - 1] != 'a' and self.__data[random_row][random_column + 1] != 'a':
                    self.__data[random_row][random_column] = 'a'
                    apple_counter += 1

    def move(self, new_direction, old_direction, pace):
        if old_direction == new_direction:
            pass
        else:
            for _ in range(pace):
                if new_direction == 'up':
                    if self.__head_position_row - 1 >= 0:
                        if self.__data[self.__head_position_row - 1][self.__head_position_column] != '+':
                            if self.__data[self.__head_position_row - 1][self.__head_position_column] == ' ':  # Moves normally
                                self.__data[self.__head_position_row - 1][self.__head_position_column] = '*'
                                self.__head_position_row = self.__head_position_row - 1

                                self.__snake_body.append([self.__head_position_row, self.__head_position_column])
                                self.__data[self.__snake_body[0][0]][self.__snake_body[0][1]] = ' '
                                self.__snake_body.pop(0)
                                for index in range(len(self.__snake_body) - 1):
                                    self.__data[self.__snake_body[index][0]][self.__snake_body[index][1]] = '+'
                            else:  # Eats
                                self.__data[self.__head_position_row - 1][self.__head_position_column] = '*'
                                self.__data[self.__head_position_row][self.__head_position_column] = '+'
                                self.__head_position_row = self.__head_position_row - 1
                                self.__snake_body.append([self.__head_position_row, self.__head_position_column])
                                self.add_apples(1)
                        else:
                            raise AssertionError("You lost!")
                    else:
                        raise AssertionError("You lost!")
                elif new_direction == 'down':
                    if self.__head_position_row + 1 < self.__size:
                        if self.__data[self.__head_position_row + 1][self.__head_position_column] != '+':
                            if self.__data[self.__head_position_row + 1][self.__head_position_column] == ' ':
                                self.__data[self.__head_position_row + 1][self.__head_position_column] = '*'
                                self.__head_position_row = self.__head_position_row + 1

                                self.__snake_body.append([self.__head_position_row, self.__head_position_column])
                                self.__data[self.__snake_body[0][0]][self.__snake_body[0][1]] = ' '
                                self.__snake_body.pop(0)
                                for index in range(len(self.__snake_body) - 1):
                                    self.__data[self.__snake_body[index][0]][self.__snake_body[index][1]] = '+'
                            else:
                                self.__data[self.__head_position_row + 1][self.__head_position_column] = '*'
                                self.__data[self.__head_position_row][self.__head_position_column] = '+'
                                self.__head_position_row = self.__head_position_row + 1
                                self.__snake_body.append([self.__head_position_row, self.__head_position_column])
                                self.add_apples(1)
                        else:
                            raise AssertionError("You lost!")
                    else:
                        raise AssertionError("You lost!")
                elif new_direction == 'left':
                    if self.__head_position_column - 1 >= 0:
                        if self.__data[self.__head_position_row][self.__head_position_column - 1] != '+':
                            if self.__data[self.__head_position_row][self.__head_position_column - 1] == ' ':
                                self.__data[self.__head_position_row][self.__head_position_column - 1] = '*'
                                self.__head_position_column = self.__head_position_column - 1

                                self.__snake_body.append([self.__head_position_row, self.__head_position_column])
                                self.__data[self.__snake_body[0][0]][self.__snake_body[0][1]] = ' '
                                self.__snake_body.pop(0)
                                for index in range(len(self.__snake_body) - 1):
                                    self.__data[self.__snake_body[index][0]][self.__snake_body[index][1]] = '+'
                            else:
                                self.__data[self.__head_position_row][self.__head_position_column - 1] = '*'
                                self.__data[self.__head_position_row][self.__head_position_column] = '+'
                                self.__head_position_column = self.__head_position_column - 1
                                self.__snake_body.append([self.__head_position_row, self.__head_position_column])
                                self.add_apples(1)
                        else:
                            raise AssertionError("You lost!")
                    else:
                        raise AssertionError("You lost!")
                elif new_direction == 'right':
                    if self.__head_position_column + 1 < self.__size:
                        if self.__data[self.__head_position_row][self.__head_position_column + 1] != '+':
                            if self.__data[self.__head_position_row][self.__head_position_column + 1] == ' ':
                                self.__data[self.__head_position_row][self.__head_position_column + 1] = '*'
                                self.__head_position_column = self.__head_position_column + 1

                                self.__snake_body.append([self.__head_position_row, self.__head_position_column])
                                self.__data[self.__snake_body[0][0]][self.__snake_body[0][1]] = ' '
                                self.__snake_body.pop(0)
                                for index in range(len(self.__snake_body) - 1):
                                    self.__data[self.__snake_body[index][0]][self.__snake_body[index][1]] = '+'
                            else:
                                self.__data[self.__head_position_row][self.__head_position_column + 1] = '*'
                                self.__data[self.__head_position_row][self.__head_position_column] = '+'
                                self.__head_position_column = self.__head_position_column + 1
                                self.__snake_body.append([self.__head_position_row, self.__head_position_column])
                                self.add_apples(1)
                        else:
                            raise AssertionError("You lost!")
                    else:
                        raise AssertionError("You lost!")

    def __str__(self):
        table = Texttable()
        for index in range(self.__size):
            table.add_row(self.__data[index])
        return table.draw()
