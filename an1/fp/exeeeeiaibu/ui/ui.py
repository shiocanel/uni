from repository.repository_exception import RepositoryException
from domain.validators.validation_exception import ValidationException

class UI:
    def __init__(self, service_client):
        self.__service_client = service_client

    def read(self, text, expected_type):
        while True:
            data = input(text)

            try:
                data = expected_type(data)
                return data
            except ValueError:
                print("INVALID DATA TYPE")

    def start(self):
        while True:
            print("==MENU==")
            print("1) Manage Clients")
            print("0) Exit")
            print("==MENU==")

            option = self.read("Option: ", str)

            if option == "1":
                self.manage_clients()
            elif option == "0":
                print("Sa fie cu sanatate!!")
                return
            else:
                print("Invalid option!")

    def manage_clients(self):
        while True:
            print("==MENU==")
            print("1) Add Client")
            print("2) Update Client")
            print("3) Delete Client")
            print("4) See All Clients")
            
            print("0) Exit")
            print("==MENU==")

            option = self.read("Option: ", str)

            if option == "1":
                try:
                    id = self.read("ID: ", int)
                    name = self.read("Name: ", str)
                    cnp = self.read("CNP: ", str)
                    self.__service_client.add_client(id, name, cnp)
                    print("==Client added successfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "2":
                try:
                    id = self.read("ID: ", int)
                    name = self.read("Name: ", str)
                    cnp = self.read("CNP: ", str)

                    self.__service_client.update_client(id, name, cnp)
                    print("==Client updated successfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "3":
                try:
                    id = self.read("ID: ", int)
                    self.__service_client.delete_client(id)
                    print("==Client deleted successfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "4":
                try:
                    clients = self.__service_client.get_all_clients()

                    print("==Clients==")
                    for client in clients:
                        print()
                        print(f"ID: {client.get_id()}")
                        print(f"Name: {client.get_name()}")
                        print(f"CNP: {client.get_cnp()}")
                        print()
                    print("==Clients==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "0":
                return
            else:
                print("Invalid option!")
        