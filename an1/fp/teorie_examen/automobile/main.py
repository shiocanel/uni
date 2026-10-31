from repository.repository import Repository
from controller.service_automobil import ServiceAutomobil
from ui.ui import UI

def main():
    repo = Repository()
    service = ServiceAutomobil(repo)
    ui = UI(service)
    ui.start()


if __name__ == "__main__":
    main()

    # exportu face un fisier