from texttable import Texttable
from unittest import TestCase
import random


class Board:
    def __init__(self, width=7, height=6):
        """
        The constructor of the board class creates the board as a matrix with empty spaces to begin with
        :param width: represents the width of the board
        :param height: represents the height of the board
        """
        self.__width = width
        self.__height = height
        self.__board = [[' ' for _ in range(width)] for _ in range(height)]

    @property
    def width(self):
        """
        This property is a getter for the width
        """
        return self.__width

    @property
    def height(self):
        """
        This property is a getter for the height
        """
        return self.__height

    def is_valid_column(self, column: int):
        """
        This method checks if a given column is in the valid range of the board
        :return: true if the given column is valid, false otherwise
        """
        start_index = 0
        if not (start_index <= column < self.width):
            return False
        return True

    def is_not_full_column(self, column: int):
        """
        This method checks if a given column if full or not
        :return: true if the column is not full, false otherwise
        """
        first_row = 0
        if self.__board[first_row][column] == ' ':
            return True
        return False

    def move(self, symbol, column: int):
        """
        This method "drops" the symbol "piece" in a given column
        :return: True if the move was made with success
        Raises AssertionError if the given column is not valid or is full
        """
        if not self.is_valid_column(column):
            raise AssertionError("Column is not valid!")
        if not self.is_not_full_column(column):
            raise AssertionError("Column is full")
        for i in range(self.height - 1, -1, -1):
            if self.__board[i][column] == " ":
                self.__board[i][column] = symbol
                return True

    def computer_move(self, computer_symbol, opponent_symbol):
        """
        This method plays the move of the computer in the following order: if there exists a winning move that the computer can perform, it will play it,
        if there exists an opponent move that could possibly win his game, it will block it, else it just plays a random move.
        :param opponent_symbol: the user's playing symbol
        :param computer_symbol: the computer's playing symbol
        :return: the column which is played by the computer
        """
        # Check for winning moves
        for column in range(0, self.width):
            if self.is_winning_move(computer_symbol, column):
                self.move(computer_symbol, column)
                return column

        # Check for opponent's winning moves and block them
        for column in range(0, self.width):
            if self.is_winning_move(opponent_symbol, column):
                self.move(computer_symbol, column)
                return column

        # Play a random move
        valid_columns = [column for column in range(0, self.width) if self.is_not_full_column(column)]
        if valid_columns:
            column = random.choice(valid_columns)
            self.move(computer_symbol, column)
            return column
        return None

    def is_winning_move(self, symbol, column: int):
        """
        This method checks if a possible move could win the game for the symbol's player
        :param symbol: symbol of the player
        :param column: column of current position to verify
        :return: true if there exist a winning move, false otherwise
        """
        if self.is_not_full_column(column):
            row = 0
            for row_index in range(self.height - 1, -1, -1):
                if self.__board[row_index][column] == ' ':
                    row = row_index
                    break
            # Horizontal check
            if self.count_consecutive_symbols(symbol, row, column, 0, 1) + self.count_consecutive_symbols(symbol, row, column, 0, -1) >= 3:
                return True

            # Vertical check
            if self.count_consecutive_symbols(symbol, row, column, 1, 0) + self.count_consecutive_symbols(symbol, row, column, -1, 0) >= 3:
                return True

            # \ diagonal check
            if self.count_consecutive_symbols(symbol, row, column, 1, 1) + self.count_consecutive_symbols(symbol, row, column, -1, -1) >= 3:
                return True

            # / diagonal check
            if self.count_consecutive_symbols(symbol, row, column, 1, -1) + self.count_consecutive_symbols(symbol, row, column, -1, 1) >= 3:
                return True

        return False

    def count_consecutive_symbols(self, symbol, row, column, row_step, column_step):
        """
        This method counts how many consecutive symbols are from a given row and column, with a given row and column step, excepting the current position's symbol
        :param symbol: the symbol we are looking for
        :param row: row index of current position
        :param column: column index of current position
        :param row_step: the step of the row
        :param column_step: the step of the column
        :return: how many consecutive symbols there are
        """
        symbol_count = 0
        for index in range(1, 4):
            next_row = row + index * row_step
            next_column = column + index * column_step
            if 0 <= next_row < self.height and 0 <= next_column < self.width:
                if self.__board[next_row][next_column] == symbol:
                    symbol_count += 1
                else:
                    break
            else:
                return symbol_count
        return symbol_count

    def is_won_board(self):
        """
        This method checks every possible combination of winning in connect four
        :return: true if somebody won, false otherwise
        """
        # Horizontal check
        for row in range(6):
            for column in range(4):
                if self.__board[row][column] != ' ':
                    if self.__board[row][column] == self.__board[row][column + 1]:
                        if self.__board[row][column] == self.__board[row][column + 2]:
                            if self.__board[row][column] == self.__board[row][column + 3]:
                                return True

        # Vertical check
        for row in range(7):
            for column in range(3):
                if self.__board[column][row] != ' ':
                    if self.__board[column][row] == self.__board[column + 1][row]:
                        if self.__board[column][row] == self.__board[column + 2][row]:
                            if self.__board[column][row] == self.__board[column + 3][row]:
                                return True

        # Right diagonal check \
        for row in range(3):
            for column in range(4):
                if self.__board[row][column] != ' ':
                    if self.__board[row][column] == self.__board[row + 1][column + 1]:
                        if self.__board[row][column] == self.__board[row + 2][column + 2]:
                            if self.__board[row][column] == self.__board[row + 3][column + 3]:
                                return True

        # Left diagonal check /
        for row in range(3):
            column = 6
            while column > 2:
                if self.__board[row][column] != ' ':
                    if self.__board[row][column] == self.__board[row + 1][column - 1]:
                        if self.__board[row][column] == self.__board[row + 2][column - 2]:
                            if self.__board[row][column] == self.__board[row + 3][column - 3]:
                                return True
                column -= 1

        return False

    def draw_game(self):
        """
        This method verifies if the game resulted in a draw, by checking if every column is full
        :return: true if the game is a draw, false otherwise
        """
        for column in range(0, self.width):
            if self.is_not_full_column(column):
                return False
        return True

    def __str__(self):
        """
        This method transforms the board table into a string representation
        :return: the string representation
        """
        table = Texttable()
        header_list = []
        for i in range(self.__width):
            header_list.append(str(i + 1))
        table.header(header_list)
        for i in range(self.__height):
            table.add_row(self.__board[i])
        return table.draw()


class BoardTest(TestCase):
    def setUp(self):
        self.board = Board()

    def test_width(self):
        self.assertEqual(self.board.width, 7)

    def test_height(self):
        self.assertEqual(self.board.height, 6)

    def test_is_not_full_column(self):
        empty_column = 4
        full_column = 0
        self.board.move('X', 0)
        self.board.move('O', 0)
        self.board.move('X', 0)
        self.board.move('O', 0)
        self.board.move('X', 0)
        self.board.move('O', 0)
        self.assertTrue(self.board.is_not_full_column(empty_column))
        self.assertFalse(self.board.is_not_full_column(full_column))

    def test_is_valid_column(self):
        valid_column = 2
        invalid_column = 10
        self.assertTrue(self.board.is_valid_column(valid_column))
        self.assertFalse(self.board.is_valid_column(invalid_column))

    def test_move(self):
        symbol = 'X'
        self.board.move('X', 0)
        self.board.move('O', 0)
        self.board.move('X', 0)
        self.board.move('O', 0)
        self.board.move('X', 0)
        self.board.move('O', 0)
        with self.assertRaises(AssertionError):
            self.board.move(symbol, -1)
        with self.assertRaises(AssertionError):
            self.board.move(symbol, 0)
        self.assertTrue(self.board.move(symbol, 5))

    def test_computer_move_blocking(self):
        # Blocking opponent
        self.board.move('X', 0)
        self.board.move('X', 1)
        self.board.move('X', 2)
        column = self.board.computer_move('O', 'X')
        self.assertEqual(column, 3)

    def test_computer_move_win(self):
        self.board.move('O', 0)
        self.board.move('O', 1)
        self.board.move('O', 2)
        column = self.board.computer_move('O', 'X')
        self.assertEqual(column, 3)

    def test_computer_move_random(self):
        column = self.board.computer_move('O', 'X')
        self.assertIn(column, [0, 1, 2, 3, 4, 5, 6])

    def test_is_winning_move(self):
        self.board.move('O', 0)
        self.board.move('O', 1)
        self.board.move('O', 2)
        self.assertTrue(self.board.is_winning_move('O', 3))
        self.assertFalse(self.board.is_winning_move('O', 0))

    def test_count_consecutive_symbols(self):
        self.board.move('X', 0)
        self.board.move('X', 0)
        self.board.move('X', 0)
        self.board.move('X', 1)
        self.board.move('X', 1)
        self.assertEqual(self.board.count_consecutive_symbols('X', 5, 0, -1, 0), 2)

    def test_is_won_board_true(self):
        self.board.move('X', 6)
        self.board.move('O', 5)
        self.board.move('X', 5)
        self.board.move('0', 4)
        self.board.move('0', 4)
        self.board.move('X', 4)
        self.board.move('0', 3)
        self.board.move('0', 3)
        self.board.move('0', 3)
        self.board.move('X', 3)
        self.assertTrue(self.board.is_won_board())

    def test_is_won_board_false(self):
        self.board.move('X', 6)
        self.board.move('O', 5)
        self.board.move('X', 5)
        self.board.move('0', 4)
        self.board.move('0', 4)
        self.board.move('X', 4)
        self.assertFalse(self.board.is_won_board())

    def test_draw_game_true(self):
        self.board.move('X', 0)
        self.board.move('O', 0)
        self.board.move('X', 0)
        self.board.move('O', 0)
        self.board.move('X', 0)
        self.board.move('O', 0)

        self.board.move('O', 1)
        self.board.move('X', 1)
        self.board.move('O', 1)
        self.board.move('X', 1)
        self.board.move('O', 1)
        self.board.move('X', 1)

        self.board.move('X', 2)
        self.board.move('O', 2)
        self.board.move('X', 2)
        self.board.move('O', 2)
        self.board.move('X', 2)
        self.board.move('O', 2)

        self.board.move('X', 3)
        self.board.move('O', 3)
        self.board.move('X', 3)
        self.board.move('O', 3)
        self.board.move('X', 3)
        self.board.move('O', 3)

        self.board.move('X', 4)
        self.board.move('O', 4)
        self.board.move('X', 4)
        self.board.move('O', 4)
        self.board.move('X', 4)
        self.board.move('O', 4)

        self.board.move('O', 5)
        self.board.move('X', 5)
        self.board.move('O', 5)
        self.board.move('X', 5)
        self.board.move('O', 5)
        self.board.move('X', 5)

        self.board.move('X', 6)
        self.board.move('O', 6)
        self.board.move('X', 6)
        self.board.move('O', 6)
        self.board.move('X', 6)
        self.board.move('O', 6)

        self.assertTrue(self.board.draw_game())

    def test_draw_game_false(self):
        self.board.move('X', 0)
        self.board.move('O', 0)
        self.board.move('X', 0)
        self.board.move('O', 1)
        self.board.move('X', 1)
        self.assertFalse(self.board.draw_game())
