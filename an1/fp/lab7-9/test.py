from domain.client import Client
from domain.book import Book
from domain.rental import Rental

from domain.validators.client_validator import ClientValidator
from domain.validators.book_validator import BookValidator
from domain.validators.rental_validator import RentalValidator

from domain.validators.validation_exception import ValidationException
from repository.repository_exception import RepositoryException
from repository.repository import Repository

from controller.service_client import ServiceClient
from controller.service_book import ServiceBook
from controller.service_rental import ServiceRental

class Test:
    def __init__(self):
        pass
    
    def test(self):
        """
        functie in care rulam toate teste 
        input:
            ---
        output:
            ---
        return:
            ---
        """

        self.test_service_client()
        self.test_client_validator()
        # self.test_validaton_exception()
        self.test_client()

        self.test_service_book()
        self.test_book()
        self.test_book_validator()

        self.test_service_rental()
        self.test_rental()
        self.test_rental_validator()


        # self.test_repository_exception()
        self.test_repository_clients()
        self.test_repository_books()

        self.test_load_and_save_clients()
        self.test_load_and_save_books()
        self.test_load_and_save_rentals()
        
        print("<<ALL TESTS PASSED>>")

        

    def test_rental_validator(self):
        """
        functie care testeaza RentalValidator
        input:
            ---
        output:
            ---
        return:
            ---
        """

        rental = Rental(1, 10, 100)
        try:
            RentalValidator(rental).validate()
        except ValidationException as msg:
            raise ValidationException(msg)

        rental = Rental(-1, 10, 100)
        try:
            RentalValidator(rental).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid ID>>"

        rental = Rental(1, -10, 100)
        try:
            RentalValidator(rental).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid ID>>"

        rental = Rental(1, 10, -100)
        try:
            RentalValidator(rental).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid ID>>"

        rental = Rental(-5, -6, -7)
        try:
            RentalValidator(rental).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid ID>>"

    def test_rental(self):
        """
        functie care testeaza clasa Rental
        input:
            ---
        output:
            ---
        return:
            ---
        """

        rental = Rental(1, 10, 100)

        assert rental.get_id() == 1
        assert rental.get_book_id() == 10
        assert rental.get_client_id() == 100

        rental.set_id(2)
        assert rental.get_id() == 2

        rental.set_book_id(20)
        assert rental.get_book_id() == 20

        rental.set_client_id(200)
        assert rental.get_client_id() == 200

        rental.set_id(5)
        rental.set_book_id(50)
        rental.set_client_id(500)

        assert rental.get_id() == 5
        assert rental.get_book_id() == 50
        assert rental.get_client_id() == 500

    def test_service_rental(self):
        """
        functie care testeaza service_rental.py
        input:
            ---
        output:
            ---
        return:
            ---
        """

        self.test_add_rental()
        self.test_update_rental()
        self.test_delete_rental()
        self.test_see_all_rentals()
        self.test_most_active_users()
        self.test_clients_by_name_from_rental_service()
        self.test_never_rented()

    def test_add_rental(self):
        """
        functie care testeaza add_rental
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        service = ServiceRental(repo)

        initial = len(repo.get_all_rentals())

        service.add_rental(999, 9, 1)
        assert len(repo.get_all_rentals()) == initial + 1

        try:
            service.add_rental(999, 2, 3)
        except RepositoryException as msg:
            assert str(msg) == "<<Book already rented>>"

        try:
            service.add_rental(-1, 1, 1)
        except ValidationException as msg:
            assert "<<Invalid ID>>" in str(msg)

    def test_update_rental(self):
        """
        functie care testeaza update_rental
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        service = ServiceRental(repo)

        service.update_rental(1, 2, 3)

        found = repo.get_all_rentals()[0]
        assert found.get_book_id() == 2
        assert found.get_client_id() == 3

        try:
            service.update_rental(9999, 1, 1)
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

        try:
            service.update_rental(-10, 1, 1)
        except ValidationException as msg:
            assert "<<Invalid ID>>" in str(msg)

    def test_delete_rental(self):
        """
        functie care testeaza delete_rental
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        service = ServiceRental(repo)

        initial = len(repo.get_all_rentals())

        service.delete_rental(1)
        assert len(repo.get_all_rentals()) == initial - 1

        try:
            service.delete_rental(9999)
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

    def test_see_all_rentals(self):
        """
        functie care testeaza see_all_rentals
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        service = ServiceRental(repo)

        rentals = service.see_all_rentals()

        assert type(rentals) is list
        assert len(rentals) == len(repo.get_all_rentals())

    def test_most_active_users(self):
        """
        functie care testeaza most_active_users
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        service = ServiceRental(repo)
        result = service.most_active_users()

        assert str(result[0]) == "Ioan : 2"
        assert str(result[1]) == "Riky : 2"

    def test_clients_by_name_from_rental_service(self):
        """
        functie care testeaza sortarea by name
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        service = ServiceRental(repo)

        clients = service.clients_by_name()

        assert str(clients[0]) == "4 : Andrei"
        assert str(clients[1]) == "1 : Ioan"
        assert str(clients[2]) == "2 : Octavian"

    def test_never_rented(self):
        """
        functie care testeaza never_rented
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()

        service = ServiceRental(repo)
        never = service.never_rented()

        assert str(never[0])== "ID : 9 | Crime and Punishment"

    def test_service_book(self):
        """
        functie care testeaza service_book.py
        input:
            ---
        output:
            ---
        return:
            ---
        """

        self.test_add_book()
        self.test_update_book()
        self.test_delete_book()

    def test_delete_book(self):
        """
        functie care testeaza delete_book
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        service = ServiceBook(repo)

        initial = len(repo.get_all_books())

        service.delete_book(1)
        assert len(repo.get_all_books()) == initial - 1

        try:
            service.delete_book(999)
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

    def test_update_book(self):
        """
        functie care testeaza update_book
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        service = ServiceBook(repo)

        service.update_book(1, "New Title", "New Desc", "New Auth")

        assert repo.get_all_books()[0].get_title() == "New Title"
        assert repo.get_all_books()[0].get_description() == "New Desc"
        assert repo.get_all_books()[0].get_author() == "New Auth"

        try:
            service.update_book(999, "X", "Y", "Z")
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

    def test_add_book(self):
        """
        functie care testeaza add_book
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        service = ServiceBook(repo)

        initial = len(repo.get_all_books())

        service.add_book(100, "B", "D", "A")
        assert len(repo.get_all_books()) == initial + 1

        try:
            service.add_book(100, "X", "Y", "Z")
        except RepositoryException as msg:
            assert str(msg) == "<<Identical IDs>>"

    def test_repository_books(self):
        """
        functie care testeaza repo pentru books
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()

        books = repo.get_all_books()
        assert len(books) == 9
        assert books[0].get_title() == "1984"
        assert books[-1].get_title() == "Crime and Punishment"

        new_book = Book(100, "Test", "Test desc", "Tester")
        BookValidator(new_book).validate()
        repo.add_book(new_book)

        assert len(repo.get_all_books()) == 10
        assert repo.get_all_books()[-1].get_title() == "Test"

        dup_id_book = Book(100, "Alt", "Desc", "Auth")
        try:
            repo.add_book(dup_id_book)
        except RepositoryException as msg:
            assert str(msg) == "<<Identical IDs>>"

        updated_book = Book(100, "Updated", "Updated desc", "Updated Auth")
        repo.update_book(updated_book)

        assert repo.get_all_books()[-1].get_title() == "Updated"

        not_found = Book(999, "X", "Y", "Z")
        try:
            repo.update_book(not_found)
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

        repo.delete_book(100)
        assert len(repo.get_all_books()) == 9
        assert all(b.get_id() != 100 for b in repo.get_all_books())

        try:
            repo.delete_book(999)
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

    def test_book_validator(self):
        """
        functie care testeaza BookValidator
        input:
            ---
        output:
            ---
        return:
            ---
        """

        book = Book(1, "T", "D", "A")
        try:
            BookValidator(book).validate()
        except ValidationException as msg:
            raise ValidationException(msg)

        book = Book(-1, "T", "D", "A")
        try:
            BookValidator(book).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid ID>>"

        book = Book(1, "", "D", "A")
        try:
            BookValidator(book).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid title>>"

        book = Book(1, "T", "", "A")
        try:
            BookValidator(book).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid description>>"

        book = Book(1, "T", "D", "")
        try:
            BookValidator(book).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid author>>"

    def test_book(self):
        """
        functie care testeaza clasa Book
        input:
            ---
        output:
            ---
        return:
            ---
        """

        book = Book(1, "Title", "Desc", "Auth")
        assert book.get_id() == 1
        assert book.get_title() == "Title"
        assert book.get_description() == "Desc"
        assert book.get_author() == "Auth"

        book.set_id(2)
        book.set_title("New Title")
        book.set_description("New Desc")
        book.set_author("New Auth")

        assert book.get_id() == 2
        assert book.get_title() == "New Title"
        assert book.get_description() == "New Desc"
        assert book.get_author() == "New Auth"

    def test_repository_clients(self):
        """
        functie care testeaza clasa Repository
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()

        clients = repo.get_all_clients()
        assert len(clients) == 5
        assert clients[0].get_name() == "Ioan"
        assert clients[-1].get_name() == "Stefan"

        new_client = Client(100, "Mihai", "1981215467894")
        ClientValidator(new_client).validate()
        repo.add_client(new_client)

        assert len(repo.get_all_clients()) == 6
        assert repo.get_all_clients()[-1].get_name() == "Mihai"

        dup_id_client = Client(100, "Altul", "1991215467894")
        try:
            repo.add_client(dup_id_client)
        except RepositoryException as msg:
            assert str(msg) == "<<Identical IDs>>"

        dup_cnp_client = Client(200, "Andrei", "1981215467894")
        try:
            repo.add_client(dup_cnp_client)
        except RepositoryException as msg:
            assert str(msg) == "<<Identical CNPs>>"

        updated_client = Client(100, "Mihai Alexandru", "1981215467894")
        repo.update_client(updated_client)

        all_clients = repo.get_all_clients()
        assert all_clients[-1].get_name() == "Mihai Alexandru"

        not_found_client = Client(999, "Ion", "1990101333444")
        try:
            repo.update_client(not_found_client)
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

        repo.delete_client(100)
        all_clients = repo.get_all_clients()
        assert len(all_clients) == 5
        assert all(client.get_id() != 100 for client in all_clients)

        try:
            repo.delete_client(999)
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

    def test_client(self):
        """
        functie care testeaza clasa Client 
        input:
            ---
        output:
            ---
        return:
            ---
        """

        client = Client(1, "Mihai", "5010101221144")
        assert client.get_id() == 1
        assert client.get_name() == "Mihai"
        assert client.get_cnp() == "5010101221144"

        client.set_id(2)
        client.set_name("Andrei")
        client.set_cnp("6020201333444")

        assert client.get_id() == 2
        assert client.get_name() == "Andrei"
        assert client.get_cnp() == "6020201333444"

    def test_service_client(self):
        """
        functie care testeaza tot service_client
        input:
            ---
        output:
            ---
        return:
            ---
        """

        self.test_add_client()
        self.test_update_client()
        self.test_delete_client()

    def test_delete_client(self):
        """
        functie care testeaza delete_client
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        service = ServiceClient(repo)

        initial_length = len(repo.get_all_clients())

        service.delete_client(1)
        assert len(repo.get_all_clients()) == initial_length - 1

        try:
            service.delete_client(9999)
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

    def test_add_client(self):
        """
        functie care testeaza add_client
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        service = ServiceClient(repo)

        service.add_client(1001, "Mihai", "1971215467894")
        assert len(repo.get_all_clients()) == 6
        assert repo.get_all_clients()[5].get_name() == "Mihai"

        try:
            service.add_client(1001, "Marcel", "1971215467894")
        except RepositoryException as msg:
            assert str(msg) == "<<Identical IDs>>"

        try:
            service.add_client(2000, "Ionel", "1971215467894")
        except RepositoryException as msg:
            assert str(msg) == "<<Identical CNPs>>"

    def test_update_client(self):
        """
        functie care testeaza update_client
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        service = ServiceClient(repo)

        service.update_client(1, "Ionel", "6051218123457")
        assert repo.get_all_clients()[0].get_name() == "Ionel"
        assert repo.get_all_clients()[0].get_cnp() == "6051218123457"

        try:
            service.update_client(9999, "Andrei", "5031219222231")
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

        try:
            service.update_client(1, "Ionfsdjsdk", "6051218123457")
        except RepositoryException as msg:
            assert str(msg) == "<<Identical CNPs>>"

    def test_client_validator(self):
        """
        functie in care test client_validator
        input:
            ---
        output:
            ---
        return:
            ---
        """
        
        client = Client(1, "Ion", "5010101221144")
        try:
            ClientValidator(client).validate()
        except ValidationException as msg:
            raise ValidationException(msg)

        client = Client(-1, "Ion Popescu", "5010101221144")
        try:
            ClientValidator(client).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid ID>>"

        client = Client(2, "Ion123", "5010101221144")
        try:
            ClientValidator(client).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid name>>"

        client = Client(3, "", "5010101221144")
        try:
            ClientValidator(client).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid name>>"

        client = Client(4, "Maria", "123")
        try:
            ClientValidator(client).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid CNP>>"

        client = Client(5, "Andrei", "1960239460018")
        try:
            ClientValidator(client).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid CNP>>"

    def test_load_and_save_clients(self):
        """
        functie care testeaza citirile si modificarile din fisierul client.txt
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        clients = repo.get_all_clients()

        assert len(clients) >= 5
        assert clients[0].get_name() == "Ioan"

        og_name = clients[0].get_name()
        clients[0].set_name("Ion Test")
        repo.save_clients()

        repo2 = Repository()
        assert repo2.get_all_clients()[0].get_name() == "Ion Test"

        repo2.get_all_clients()[0].set_name(og_name)
        repo2.save_clients()

    def test_load_and_save_books(self):
        """
        functie care testeaza citirile si modificarile din fisierul books.txt
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        books = repo.get_all_books()

        assert len(books) >= 9
        assert books[0].get_title() == "1984"

        og_titlu = books[0].get_title()
        books[0].set_title("1984 TEST")
        repo.save_books()

        repo2 = Repository()
        assert repo2.get_all_books()[0].get_title() == "1984 TEST"

        repo2.get_all_books()[0].set_title(og_titlu)
        repo2.save_books()

    def test_load_and_save_rentals(self):
        """
        functie care testeaza citirile si modificarile din fisierul rentals.txt
        input:
            ---
        output:
            ---
        return:
            ---
        """

        repo = Repository()
        rentals = repo.get_all_rentals()

        assert len(rentals) >= 1
        og_id = rentals[0].get_client_id()
        rentals[0].set_client_id(999)
        repo.save_rentals()

        try:
            repo2 = Repository()
        except RepositoryException as msg:
            rentals[0].set_client_id(og_id)
            repo.save_rentals()
            assert str(msg) == "<<Client does not exist>>"
            