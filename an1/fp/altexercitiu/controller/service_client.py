from domain.client import Client
from domain.validators.client_validator import ClientValidator

class ServiceClient:
    def __init__(self, repo):
        self.__repo = repo

    def add_client(self, id, name, cnp):
        client = Client(id, name, cnp)
        ClientValidator(client).validate()
        self.__repo.add_client(client)

    def update_client(self, id, name, cnp):
        client = Client(id, name, cnp)
        ClientValidator(client).validate()
        self.__repo.update_client(client)

    def delete_client(self, id):
        self.__repo.delete_client(id)

    def get_all_clients(self):
        return self.__repo.get_all_clients()
    
    def save_clients(self):
        self.__repo.save_clients()