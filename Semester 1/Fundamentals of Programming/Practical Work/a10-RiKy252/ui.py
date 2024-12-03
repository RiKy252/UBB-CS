from domain import Board
import random


class UI:
    def __init__(self, board):
        self.board = board

    @staticmethod
    def random_start_turn(user_symbol, computer_symbol):
        user_number = 1
        random_number = random.randint(1, 2)
        if random_number == user_number:
            return user_symbol
        else:
            return computer_symbol

    def start(self):
        while True:
            user_symbol = input("Enter your playing symbol (1 character): ").strip()
            if user_symbol == "" or len(user_symbol) > 1:
                print("Try again...")
            else:
                break
        while True:
            computer_symbol = input("Enter the computer's symbol (1 character): ").strip()
            if computer_symbol == "" or len(computer_symbol) > 1:
                print("Try again...")
            else:
                break
        print("You are playing with " + user_symbol + " and the computer is playing with " + computer_symbol)
        while True:
            start = input("When you are ready to start please press Enter").strip()
            if start == "":
                break
        turn = self.random_start_turn(user_symbol, computer_symbol)
        print(self.board)
        while True:
            try:
                if turn == user_symbol:
                    user_play = int(input("It's your turn, select a column to place your piece: "))
                    self.board.is_valid_column(user_play - 1)
                    self.board.move(user_symbol, user_play - 1)
                    print(self.board)
                    if self.board.is_won_board():
                        print("You won!")
                        break
                    turn = computer_symbol
                elif turn == computer_symbol:
                    computer_column = self.board.computer_move(computer_symbol, user_symbol) + 1
                    print("Computer moved on column " + str(computer_column))
                    print(self.board)
                    if self.board.is_won_board():
                        print("Computer won!")
                        break
                    turn = user_symbol
                if self.board.draw_game():
                    print("The result is a draw!")
            except (ValueError, AssertionError) as error:
                print(error)


def main():
    board = Board()
    user = UI(board)
    user.start()


main()
