from repository.repository import Repository
from controller.service_client import ServiceClient
from ui.ui import UI
from test import Test

def main():
    test = Test()
    test.test()
    repo = Repository()
    service_clients = ServiceClient(repo)
    ui = UI(service_clients)
    ui.start()


if __name__ == "__main__":
    main()