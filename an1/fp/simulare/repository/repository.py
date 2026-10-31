from repository.repository_exception import RepositoryException
from domain.client import Client
from domain.validators.client_validator import ClientValidator

class Repository:
    def __init__(self):
        self.__clients = []

        self.load_clients("D:\\uni\\fp\\lab7-9\\data\\clients.txt")

    def load_clients(self, filename):
        with open(filename, "r") as file:
            for line in file:
                parts = line.split(",")

                id, name, cnp = parts[0].strip(), parts[1].strip(), parts[2].strip()

                client = Client(int(id), name, cnp)
                ClientValidator(client).validate()
                self.add_client(client)

    def save_clients(self):
        with open("D:\\uni\\fp\\lab7-9\\data\\clients.txt", "w") as file:
            for item in self.__clients:
                file.write(f"{item.get_id()}, {item.get_name()}, {item.get_cnp()}\n")

    def add_client(self, client):
        self.check_unique_client(client)
        self.__clients.append(client)     

    def check_unique_client(self, client, ignore_id = None):
        for local_client in self.__clients:
            if ignore_id is not None and local_client.get_id() == ignore_id:
                continue

            if local_client.get_id() == client.get_id():
                raise RepositoryException("<<Identical IDs>>")
            if local_client.get_cnp() == client.get_cnp():
                raise RepositoryException("<<Identical CNPs>>")
    
    def get_all_clients(self):
        return list(self.__clients) # copy
    
    def update_client(self, client):
        for local_client in self.__clients:
            if local_client.get_id() == client.get_id():
                self.check_unique_client(client, ignore_id=client.get_id())

                local_client.set_name(client.get_name())
                local_client.set_cnp(client.get_cnp())
                return

        raise RepositoryException("<<ID does not exist>>")

    def delete_client(self, client_id):
        for local_client in self.__clients:
            if local_client.get_id() == client_id:
                self.__clients.remove(local_client)
                return

        raise RepositoryException("<<ID does not exist>>")

