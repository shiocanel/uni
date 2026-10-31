from domain.validators.validation_exception import ValidationException
from repository.repository_exception import RepositoryException

class UI:
    def __init__(self, service_client):
        self.__service_client = service_client

    def read(self, text, expected_type):
        while True:
            try:
                data = input(text)
                data = expected_type(data)
                return data
            except ValueError:
                print("Vezi ca nu e bine ce ai introdus broski!!")

    def start(self):
        while True:
            print("\n\n")
            print("==MANAGE CLIENTS==")
            print("1) Add Client")
            print("2) Update Client")
            print("3) Delete Client")
            print("4) See All Clients")
            print("5) Save Clients")
            print("0) Exit")
            print("==MANAGE CLIENTS==")
            option = self.read("Option: ", str)
            print("\n\n")

            if option == "1":
                try:
                    id = self.read("ID: ", int)
                    name = self.read("Name: ", str)
                    cnp = self.read("CNP: ", str)

                    self.__service_client.add_client(id, name, cnp)
                    print("==Client added successfully==")
                except (ValidationException, RepositoryException) as ex:
                    print(ex.get_message())
            elif option == "2":
                try:
                    id = self.read("ID: ", int)
                    name = self.read("Name: ", str)
                    cnp = self.read("CNP: ", str)

                    self.__service_client.update_client(id, name, cnp)
                    print("==Client updated successfully==")
                except (ValidationException, RepositoryException) as ex:
                    print(ex.get_message())
            elif option == "3":
                try:
                    id = self.read("ID: ", int)

                    self.__service_client.delete_client(id)
                    print("==Client deleted successfully==")
                except (ValidationException, RepositoryException) as ex:
                    print(ex.get_message())
            elif option == "4":
                clients = self.__service_client.get_all_clients()

                print("==Clients==")
                for client in clients:
                    print()
                    print(f"ID: {client.get_id()}")
                    print(f"Name: {client.get_name()}")
                    print(f"CNP: {client.get_cnp()}")
                    print()
                
                print("==Clients==")
            elif option == "5":
                self.__service_client.save_clients()
                print("==Clients saved successfully==")
            elif option == "0":
                print("Sa fie cu bine!!")
                return
            else:
                print("BOULE!!!")