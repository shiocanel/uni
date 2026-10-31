from repository.TicTacToeRepository import TicTacToeRepository
from controller.TicTacToeService import TicTacToeService
from ui.ui import UI
from test import Test

def main():
    test = Test()
    test.test()
    repo = TicTacToeRepository()
    service = TicTacToeService(repo)
    ui = UI(service)
    ui.start()

if __name__ == "__main__":
    main()