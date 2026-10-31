from domain.client import Client
from domain.validators.client_validator import ClientValidator
from repository.repository_exception import RepositoryException

class Repository:
    def __init__(self):
        self.__clients = []

        self.load_clients()

    def load_clients(self):
        with open("D:\\uni\\fp\\exeeeeiaibu\\data\\client.txt", "r") as file:
            for line in file:
                parts = line.split(",")

                id, name, cnp = int(parts[0].strip()), parts[1].strip(), parts[2].strip()
                client = Client(id, name, cnp)
                ClientValidator(client).validate()

                self.add_client(client)

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
        return list(self.__clients)

    def update_client(self, client):
        for local_clinet in self.__clients:
            if local_clinet.get_id() == client.get_id():    
                self.check_unique_client(client, client.get_id())

                local_clinet.set_name(client.get_name())
                local_clinet.set_cnp(client.get_cnp())
                return
            
        raise RepositoryException("<<ID DOES NOT EXIST>>")

    def delete_client(self, client_id):
        for local_client in self.__clients:
            if local_client.get_id() == client_id:
                self.__clients.remove(local_client)
                return
            
        raise RepositoryException("<<ID DOES NOT EXIST>>")
            