from domain.client import Client
from domain.validators.client_validator import ClientValidator
from repository.repository_exception import RepositoryException

class Repository:
    def __init__(self):
        self.__clients = []

        self.load_clients()

    def load_clients(self):
        with open("D:\\uni\\fp\\altexercitiu\\data\\clients.txt", "r") as file:
            for line in file:
                parts = line.split(",")

                id, name, cnp = int(parts[0].strip()), parts[1].strip(), parts[2].strip()

                client = Client(id, name, cnp)
                ClientValidator(client).validate()
                self.__clients.append(client)

    def save_clients(self):
        with open("D:\\uni\\fp\\altexercitiu\\data\\clients.txt", "w") as file:
            for client in self.__clients:
                file.write(f"{client.get_id()}, {client.get_name()}, {client.get_cnp()}\n")
``
    def check_unique(self, client, ignore_id = None):
        for local_client in self.__clients:
            if ignore_id is not None and local_client.get_id() == ignore_id:
                continue
            
            if local_client.get_id() == client.get_id():
                raise RepositoryException("<<IDENTICAL IDs>>")
            if local_client.get_cnp() == client.get_cnp():
                raise RepositoryException("<<IDENTICAL CNPs>>")

    def add_client(self, client):
        self.check_unique(client)
        self.__clients.append(client)

    def update_client(self, client):
        self.check_unique(client, client.get_id())

        for local_client in self.__clients:
            if local_client.get_id() == client.get_id():
                local_client.set_name(client.get_name())
                local_client.set_cnp(client.get_cnp())
                return
            
        raise RepositoryException("<<ID DOES NOT EXIST>>")

    def get_all_clients(self):
        return self.__clients
    
    def delete_client(self, id):
        for local_client in self.__clients:
            if local_client.get_id() == id:
                self.__clients.remove(local_client)
                return
            
        raise RepositoryException("<<ID DOES NOT EXIST>>")
    
