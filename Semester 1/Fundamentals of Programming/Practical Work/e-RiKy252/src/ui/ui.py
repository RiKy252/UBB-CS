from src.settings import size, apples
from src.Domain.domain import Board


class UI:
    def __init__(self, board):
        self.board = board
        self.direction = 'up'

    def start(self):
        try:
            while True:
                try:
                    print(self.board)
                    user_command = input(">").strip().lower().split(" ")
                    if user_command[0] == 'move' and len(user_command) == 1:
                        self.board.move(self.direction, '', 1)
                    elif user_command[0] == 'move' and len(user_command) == 2 and type(int(user_command[1])) == int:
                        self.board.move(self.direction, '', int(user_command[1]))
                    elif (user_command[0] == 'up' or user_command[0] == 'right' or user_command[0] == 'left' or user_command[0] == 'down') and len(user_command) == 1:
                        if user_command[0] == 'up' and self.direction == 'down':
                            print("Invalid direction!")
                        elif user_command[0] == 'up':
                            self.board.move('up', self.direction, 1)
                            self.direction = 'up'
                        elif user_command[0] == 'down' and self.direction == 'up':
                            print("Invalid direction!")
                        elif user_command[0] == 'down':
                            self.board.move('down', self.direction, 1)
                            self.direction = 'down'
                        elif user_command[0] == 'right' and self.direction == 'left':
                            print("Invalid direction!")
                        elif user_command[0] == 'right':
                            self.board.move('right', self.direction, 1)
                            self.direction = 'right'
                        elif user_command[0] == 'left' and self.direction == 'right':
                            print("Invalid direction!")
                        else:
                            self.board.move('left', self.direction, 1)
                            self.direction = 'left'
                    else:
                        print("Invalid command!")
                except ValueError as error:
                    print(error)
        except AssertionError as error:
            print(error)


def main():
    board = Board(size, apples)
    user = UI(board)
    user.start()


main()
