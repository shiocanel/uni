from ui import menu
from test import test_program

if __name__ == "__main__":
    pachete = []
    undo_list = []

    test_program()
    menu(pachete, undo_list)