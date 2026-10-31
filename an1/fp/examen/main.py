from repository.repository import Repository
from controller.melodii_service import MelodiiService
from ui.ui import UI
from test import Test

def main():
    """
    functie de main
    """

    test = Test()
    test.test()

    repo = Repository()
    service = MelodiiService(repo)
    ui = UI(service)
    ui.start()


if __name__ == "__main__":
    main()



