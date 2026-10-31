from repository.repository_exception import RepositoryException
from domain.client import Client
from domain.book import Book
from domain.rental import Rental
from domain.validators.client_validator import ClientValidator
from domain.validators.book_validator import BookValidator
from domain.validators.rental_validator import RentalValidator

class Repository:
    def __init__(self):
        """
        constructor in care initializam cu date listele clients si books si rentals
        input:
            ---
        output:
            ---
        return:
            ---
        """

        self.__clients = []
        self.__books = []
        self.__rentals = []

        self.load_clients("D:\\uni\\fp\\lab7-9\\data\\clients.txt")
        self.load_books("D:\\uni\\fp\\lab7-9\\data\\books.txt")
        self.load_rentals("D:\\uni\\fp\\lab7-9\\data\\rentals.txt")

    def load_clients(self, filename):
        """
        functie care citeste datele de clienti din filename
        input:
            - filename (string) (path)
        output:
            ---
        return:
            ---
        """

        with open(filename, "r") as file:
            for line in file:
                parts = line.split(",")

                id, name, cnp = parts[0].strip(), parts[1].strip(), parts[2].strip()

                client = Client(int(id), name, cnp)
                ClientValidator(client).validate()
                self.add_client(client)

    def load_books(self, filename):
        """
        functie care citeste datele de carti din filename
        input:
            - filename (string) (path)
        output:
            ---
        return:
            ---
        """

        with open(filename, "r") as file:
            for line in file:
                parts = line.split(",")

                id, title, description, author = parts[0].strip(), parts[1].strip(), parts[2].strip(), parts[3].strip()

                book = Book(int(id), title, description, author)
                BookValidator(book).validate()
                self.add_book(book)

    def load_rentals(self, filename):
        """
        functie care citeste datele de inchirieri din filename
        input:
            - filename (string) (path)
        output:
            ---
        return:
            ---
        """

        with open(filename, "r") as file:
            for line in file:
                parts = line.split(",")

                id, id_book, id_client = parts[0].strip(), parts[1].strip(), parts[2].strip()

                rental = Rental(int(id), int(id_book), int(id_client))
                RentalValidator(rental).validate()
                self.add_rental(rental)     

    def save_clients(self):
        """
        functie care salveaza clientii in fisier
        input:
            ---
        output:
            ---
        return:
            ---
        """
        
        with open("D:\\uni\\fp\\lab7-9\\data\\clients.txt", "w") as file:
            for item in self.__clients:
                file.write(f"{item.get_id()}, {item.get_name()}, {item.get_cnp()}\n")

    def save_books(self):
        """
        functie care salveaza cartile in fisier
        input:
            ---
        output:
            ---
        return:
            ---
        """
        

        with open("D:\\uni\\fp\\lab7-9\\data\\books.txt", "w") as file:
            for item in self.__books:
                file.write(f"{item.get_id()}, {item.get_title()}, {item.get_description()}, {item.get_author()}\n")
    
    def save_rentals(self):
        """
        functie care salveaza inchirierile in fisier
        input:
            ---
        output:
            ---
        return:
            ---
        """
        
        with open("D:\\uni\\fp\\lab7-9\\data\\rentals.txt", "w") as file:
            for item in self.__rentals:
                file.write(f"{item.get_id()}, {item.get_book_id()}, {item.get_client_id()}\n")

    def add_rental(self, rental):
        """
        functie in care adaugam un rental
        input:
            - rental (Rental)
        output:
            ---
        return:
            ---
        """

        self.check_unique_rental(rental)
        self.__rentals.append(rental) 
    
    def check_unique_rental(self, rental, ignore_id = None):
        """
        functie in care verificam daca lista are id unic
        sau daca rentalu pe care dorim sa il adaugam este unic in lista
        input:
            - rental (Rental)
            - ignore_id = None (int) (id-ul rentalului care o dorim sa o schimbam)
        output:
            ---
        return:
            ---
        """

        if rental.get_book_id() > len(self.__books):
            raise RepositoryException("<<Book does not exist>>")

        if rental.get_client_id() > len(self.__clients):
            raise RepositoryException("<<Client does not exist>>")

        cnt = {}
        cnt[rental.get_book_id()] = 1
        for local_rental in self.__rentals:
            if ignore_id is not None and local_rental.get_id() == ignore_id:
                continue

            if local_rental.get_id() == rental.get_id():
                raise RepositoryException("<<Identical IDs>>")
            
            if local_rental.get_book_id() in cnt:
                raise RepositoryException("<<Book already rented>>")
            
            cnt[local_rental.get_book_id()] = 1
    
    def get_all_rentals(self):
        """
        functie care returneaza o copie a listei rentals
        pentru a evita schimbari nedorite
        input:
            ---
        output:
            ---
        return:
            - rentals (list)
        """

        return list(self.__rentals)
    
    def update_rental(self, rental):
        """
        functie care modifica un rental dandu-se un id
        input:
            - rental (Rental)
        output:
            ---
        return:
            ---
        """

        for local_rental in self.__rentals:
            if local_rental.get_id() == rental.get_id():
                self.check_unique_book(rental, ignore_id=rental.get_id())

                local_rental.set_book_id(rental.get_book_id())
                local_rental.set_client_id(rental.get_client_id())
                return

        raise RepositoryException("<<ID does not exist>>")
    
    def delete_rental(self, rental_id):
        """
        functie care sterge un rental dandu-se un id
        input:
            - rental_id (int)
        output:
            ---
        return:
            ---
        """

        for local_rental in self.__rentals:
            if local_rental.get_id() == rental_id:
                self.__rentals.remove(local_rental)
                return

        raise RepositoryException("<<ID does not exist>>")

    def add_book(self, book):
        """
        functie in care adaugam o carte
        input:
            - book (Book)
        output:
            ---
        return:
            ---
        """

        self.check_unique_book(book)
        self.__books.append(book) 
    
    def check_unique_book(self, book, ignore_id = None):
        """
        functie in care verificam daca lista are id unic
        sau daca carte pe care dorim sa o adaugam este unica in lista
        input:
            - book (Book)
            - ignore_id = None (int) (id-ul cartii care o dorim sa o schimbam)
        output:
            ---
        return:
            ---
        """

        for local_book in self.__books:
            if ignore_id is not None and local_book.get_id() == ignore_id:
                continue

            if local_book.get_id() == book.get_id():
                raise RepositoryException("<<Identical IDs>>")
    
    def get_all_books(self):
        """
        functie care returneaza o copie a listei books
        pentru a evita schimbari nedorite
        input:
            ---
        output:
            ---
        return:
            - books (list)
        """

        return list(self.__books)
    
    def update_book(self, book):
        """
        functie care modifica o carte dandu-se un id
        input:
            - book (Book)
        output:
            ---
        return:
            ---
        """

        for local_book in self.__books:
            if local_book.get_id() == book.get_id():
                self.check_unique_book(book, ignore_id=book.get_id())

                local_book.set_title(book.get_title())
                local_book.set_description(book.get_description())
                local_book.set_author(book.get_author())
                return

        raise RepositoryException("<<ID does not exist>>")
    
    def delete_book(self, book_id):
        """
        functie care sterge o carte dandu-se un id
        input:
            - book_id (int)
        output:
            ---
        return:
            ---
        """

        for local_book in self.__books:
            if local_book.get_id() == book_id:
                self.__books.remove(local_book)
                return

        raise RepositoryException("<<ID does not exist>>")

    def add_client(self, client):
        """
        functie in care adaugam un client
        input:
            - client (Client)
        output:
            ---
        return:
            ---
        """

        self.check_unique_client(client)
        self.__clients.append(client)     

    def check_unique_client(self, client, ignore_id = None):
        """
        functie in care verificam daca lista are id si cnp unic
        sau daca clientul pe care dorim sa-l adaugam este unic in lista
        input:
            - client (Client)
            - ignore_id = None (int) (id-ul clientului pe care dorim sa-l schimbam)
        output:
            ---
        return:
            ---
        """

        for local_client in self.__clients:
            if ignore_id is not None and local_client.get_id() == ignore_id:
                continue

            if local_client.get_id() == client.get_id():
                raise RepositoryException("<<Identical IDs>>")
            if local_client.get_cnp() == client.get_cnp():
                raise RepositoryException("<<Identical CNPs>>")
    
    def get_all_clients(self):
        """
        functie care returneaza o copie a listei
        pentru a evita schimbari nedorite
        input:
            ---
        output:
            ---
        return:
            - clients (list)
        """

        return list(self.__clients) # copy
    
    def update_client(self, client):
        """
        functie care modifica un client dandu-se un id
        input:
            - client (Client)
        output:
            ---
        return:
            ---
        """

        for local_client in self.__clients:
            if local_client.get_id() == client.get_id():
                self.check_unique_client(client, ignore_id=client.get_id())

                local_client.set_name(client.get_name())
                local_client.set_cnp(client.get_cnp())
                return

        raise RepositoryException("<<ID does not exist>>")

    def delete_client(self, client_id):
        """
        functie care sterge un client dandu-se un id
        input:
            - client_id (int)
        output:
            ---
        return:
            ---
        """
        
        for local_client in self.__clients:
            if local_client.get_id() == client_id:
                self.__clients.remove(local_client)
                return

        raise RepositoryException("<<ID does not exist>>")
