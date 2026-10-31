from repository.repository_exception import RepositoryException
from domain.validators.validation_exception import ValidationException

class UI:
    def __init__(self, service_client):
        """
        constructor care initializeaza service_client
        input:
            - service_client (Service)
        output:
            ---
        return:
            ---
        """

        self.__service_client = service_client 

    def read(self, text, expected_type):
        while True:
            data = input(text)
            try:
                data = expected_type(data)
                return data
            except ValueError:
                print("Invalid type!")

    def start(self):
        """
        functie de ui pentru menu
        input:
            - option (string)
        output:
            ---
        return:
            ---
        """

        while True:
            print("\n\n")
            print("======MENU======")
            print("1. Manage Clients")
            print("0. Exit")
            print("======MENU======")

            option = input("Option: ")
            print("\n\n")

            if(option == "1"):
                self.manage_clients()
            elif(option == "0"):
                print("Sa fie cu sanatate!!")
                break
            else:
                print("<<INVALID OPTION>>")

    def manage_clients(self):
        """
        functie de ui pentru a manage_clients
        input:
            - option (string)
        output:
            ---
        return:
            ---
        """
        
        while True:
            print("\n\n")
            print("======MANAGE CLIENTS======")
            print("1. Add Client")
            print("2. Update Client")
            print("3. Delete Client")
            print("4. See All Clients")
            print("5. Generate x Clients")
            print("6. Save Clients")
            print("0. Back")
            print("======MANAGE CLIENTS======")

            option = input("Option: ")
            print("\n\n")

            if(option == "1"):
                try:
                    id = self.read("ID: ", int)
                    name = self.read("Name: ", str)
                    cnp = self.read("CNP: ", str)
                    self.__service_client.add_client(id, name, cnp)
                    print("==Client added successfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())       

            elif(option == "2"):
                try:
                    id = self.read("ID: ", int)
                    name = self.read("Name: ", str)
                    cnp = self.read("CNP: ", str)
                    self.__service_client.update_client(id, name, cnp)
                    print("==Client updated successfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())  

            elif(option == "3"):
                try:
                    id = self.read("ID: ", int)
                    self.__service_client.delete_client(id)
                    print("==Client deleted successfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())        

            elif(option == "4"):
                clients = self.__service_client.see_all_clients()

                print("==CLIENTS==\n")
                for client in clients:
                    print(f"ID: {client.get_id()}\nName: {client.get_name()}\nCNP: {client.get_cnp()}\n\n")
                print("==CLIENTS==")
            elif(option == "5"):
                x = self.read("X: ", int)
                self.__service_client.generate(x)
                print("==Clients generated successfully==")
            elif(option == "6"):
                self.__service_client.save_clients()
                print("==Clients Saved Successfully==")
            elif(option == "0"):
                break
            else:
                print("<<INVALID OPTION>>") 