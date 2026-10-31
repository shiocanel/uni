from repository.repository_exception import RepositoryException
from domain.validators.validation_exception import ValidationException

class UI:
    def __init__(self, service_client, service_book, service_rental):
        """
        constructor care initializeaza service_client si service_book
        input:
            - service_client (Service)
            - service_book (Service)
        output:
            ---
        return:
            ---
        """

        self.__service_client = service_client 
        self.__service_book = service_book
        self.__service_rental = service_rental

    def read(self, text, expected_type):
        """
        functie care citeste date asteptand un anumit expected_type
        input:
            - text (string) (mesaj pentru user)
            - expected_type (type) 
        output:
            ---
        return:
            - data (expected_type) (data citita de user)
        """

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
            print("2. Manage Books")
            print("3. Reports")
            print("0. Exit")
            print("======MENU======")

            option = input("Option: ")
            print("\n\n")

            if(option == "1"):
                self.manage_clients()
            elif(option == "2"):
                self.manage_books()
            elif(option == "3"):
                self.manage_rentals()
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

    def manage_books(self):
        """
        functie de ui pentru a manage_books
        input:
            - option (string)
        output:
            ---
        return:
            ---
        """
        
        while True:
            print("\n\n")
            print("======MANAGE BOOKS======")
            print("1. Add Book")
            print("2. Update Book")
            print("3. Delete Book")
            print("4. See All Books")
            print("5. Generate x Books")
            print("6. Save Books")
            print("0. Back")
            print("======MANAGE BOOKS======")

            option = input("Option: ")
            print("\n\n")

            if(option == "1"):
                try:
                    id = self.read("ID: ", int)
                    title = self.read("Title: ", str)
                    description = self.read("Description: ", str)
                    author = self.read("Author: ", str)
                    self.__service_book.add_book(id, title, description, author)
                    print("==Book added successfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())       

            elif(option == "2"):
                try:
                    id = self.read("ID: ", int)
                    title = self.read("Title: ", str)
                    description = self.read("Description: ", str)
                    author = self.read("Author: ", str)
                    self.__service_book.update_book(id, title, description, author)
                    print("==Book updated successfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())  

            elif(option == "3"):
                try:
                    id = self.read("ID: ", int)
                    self.__service_book.delete_book(id)
                    print("==Book deleted successfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())        

            elif(option == "4"):
                books = self.__service_book.see_all_books()

                print("==BOOKS==\n")
                for book in books:
                    print(f"ID: {book.get_id()}\nTitle: {book.get_title()}\nDescription: {book.get_description()}\nAuthor: {book.get_author()}\n\n")
                print("==BOOKS==")
            elif(option == "5"):
                x = self.read("X: ", int)
                self.__service_book.generate(x)
                print("==Books generated successfully==")
            elif(option == "6"):
                self.__service_book.save_books()
                print("==Books Saved Successfully==")
            elif(option == "0"):
                break
            else:
                print("<<INVALID OPTION>>") 

    def manage_rentals(self):
        """
        functie de ui pentru a manage_rentals
        input:
            - option (string)
        output:
            ---
        return:
            ---
        """
        
        while True:
            print("\n\n")
            print("======MANAGE RENTALS======")
            print("1. Add Rental")
            print("2. Update Rental")
            print("3. Delete Rental")
            print("4. See All Rental")
            print("5. Most Active Users")
            print("6. Clients Sorted by Name")
            print("7. Books Never Rented")
            print("8. Save Rentals")
            print("9. Sort Rentals By Title and Name")
            print("0. Back")
            print("======MANAGE RENTALS======")

            option = input("Option: ")
            print("\n\n")

            if(option == "1"):
                try:
                    id = self.read("ID: ", int)
                    book_id = self.read("ID Book: ", int)
                    client_id = self.read("ID Client: ", int)

                    self.__service_rental.add_rental(id, book_id, client_id)
                    print("==Rental added successfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())       

            elif(option == "2"):
                try:
                    id = self.read("ID: ", int)
                    book_id = self.read("ID Book: ", int)
                    client_id = self.read("ID Client: ", int)

                    self.__service_rental.update_rental(id, book_id, client_id)
                    print("==Rental updated successfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())  

            elif(option == "3"):
                try:
                    id = self.read("ID: ", int)
                    self.__service_rental.delete_rental(id)
                    print("==Rental deleted successfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())        

            elif(option == "4"):
                ans = self.__service_rental.see_all_rentals()
                print("==RENTALS==\n")
                for rental in ans:
                    print(f"ID: {rental.get_id()}\nID_book: {rental.get_book_id()}\nID_client: {rental.get_client_id()}\n\n")
                print("==RENTALS==")
            elif(option == "5"):
                ans = self.__service_rental.most_active_users()
                print("==MOST ACTIVE USERS==")
                for dto in ans:
                    print(dto)
                print("==MOST ACTIVE USERS==")
            elif(option == "6"):
                ans = self.__service_rental.clients_by_name()
                print("==CLIENTS by NAME==")
                for dto in ans:
                    print(dto)
                print("==CLIENTS by NAME==")
            elif(option == "7"):
                ans = self.__service_rental.never_rented()
                print("==BOOKS NEVER RENTED==")
                for dto in ans:
                    print(dto)
                print("==BOOKS NEVER RENTED==")
            elif(option == "8"):
                self.__service_rental.save_rentals()
                print("==Rentals Saved Successfully==")
            elif(option == "9"):
                ans = self.__service_rental.sort_by_title_name()
                print("==RENTALS SORTED BY TITLE AND NAME==")
                for rental in ans:
                    id_book = rental.get_book_id()
                    id_client = rental.get_client_id()

                    print(f"{self.__service_rental.get_title_by_id(id_book)} : {self.__service_rental.get_name_by_id(id_client)}")
                print("==RENTALS SORTED BY TITLE AND NAME==")
            elif(option == "0"):
                break
            else:
                print("<<INVALID OPTION>>") 

