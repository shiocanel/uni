from domain.rental import Rental
from domain.validators.rental_validator import RentalValidator

from controller.most_active_dto import MostActiveDTO
from controller.clients_by_name_dto import ClientsByNameDTO
from controller.books_never_rented_dto import BooksNeverRentedDTO

from controller.service_sort import Sort

class ServiceRental:
    def __init__(self, repository):
        """
        functie in care initializam repo
        input:
            - repository (Repository)
        output:
            ---
        return:
            ---
        """

        self.__repo = repository

    def add_rental(self, id, book_id, client_id):
        """
        functie care adauga un rental
        input:
            - id (int)
            - book_id (int)
            - client_id (int)
        output:
            ---
        return:
            ---
        """

        rental = Rental(id, book_id, client_id)
        RentalValidator(rental).validate()
        self.__repo.add_rental(rental)

    def update_rental(self, id, book_id, client_id):
        """
        functie care modifica un rental
        input:
            - id (int)
            - book_id (int)
            - client_id (int)
        output:
            ---
        return:
            ---
        """

        rental = Rental(id, book_id, client_id)
        RentalValidator(rental).validate()

        self.__repo.update_rental(rental)

    def delete_rental(self, rental_id):
        """
        functie care sterge un rental
        input:
            - rental_id (int)
        outpu:
            ---
        return:
            ---
        """

        self.__repo.delete_rental(rental_id)

    def see_all_rentals(self):
        """
        functie care returneaza toate inchirierile
        input:
            ---
        output:
            ---
        return:
            - rentals (list)
        """
        
        return self.__repo.get_all_rentals()

    def most_active_users(self):
        """
        functie care returneaza lista celor mai activi clienti
        input:
            ---
        output:
            ---
        return:
            - ans (list)
        """

        ans = []
        cnt = {}
        for rental in self.__repo.get_all_rentals():
            if rental.get_client_id() not in cnt:
                cnt[rental.get_client_id()] = 0

            cnt[rental.get_client_id()] += 1

        aux = sorted(cnt.items(), key=lambda x: x[1], reverse=True)

        for client_id, count in aux:
            client = next(cl for cl in self.__repo.get_all_clients() if cl.get_id() == client_id)
            ans.append(MostActiveDTO(client.get_name(), count))

        return ans

    def clients_by_name(self):
        """
        functie care returneaza clientii sortati dupa nume
        input:
            ---
        output:
            ---
        return:
            - ans (list)
        """

        clients = self.__repo.get_all_clients()
        ans = sorted(clients, key=lambda c: c.get_name().lower())

        res = []
        for item in ans:
            res.append(ClientsByNameDTO(item.get_id(), item.get_name()))

        return res

    def never_rented(self):
        """
        functie care returneaza cartile care nu sunt rent-uite
        input:
            ---
        output:
            ---
        return:
            - ans (list)
        """

        ans = []
        rented_books = {r.get_book_id() for r in self.__repo.get_all_rentals()}

        for book in self.__repo.get_all_books():
            if book.get_id() not in rented_books:
                ans.append(BooksNeverRentedDTO(book.get_id(), book.get_title()))

        return ans
    
    def save_rentals(self):
        """
        functie care salveaza inchirierile intr-un fisier
        input:
            ---
        output:
            ---
        return:
            ---
        """
        
        self.__repo.save_rentals()

    def get_title_by_id(self, id, idx = 0):
        """
        returneaza titlu dupa un id
        input:
            - id (int)
        output:
            ---
        return:
            - title (string)
        """

        books = self.__repo.get_all_books()

        if idx == len(books):
            return None

        if books[idx].get_id() == id:
            return books[idx].get_title()

        return self.get_title_by_id(id, idx + 1)
            
    def get_name_by_id(self, id, idx = 0):
        """
        returneaza nume dupa un id
        input:
            - id (int)
        output:
            ---
        return:
            - name (string)

        """

        clients = self.__repo.get_all_clients()

        if idx == len(clients):
            return None

        if clients[idx].get_id() == id:
            return clients[idx].get_name()

        return self.get_name_by_id(id, idx + 1)

    def key(self, rental):
        """
        creeaza un array doar cu un rental
        input:
            - rental (Rental)
        output:
            ---
        return:
            - arr (list)
        """

        arr = [rental]
        return arr

    def cmp(self, rental1, rental2):
        """
        functie care compara doi array de rental si ii returneaza dupa titlu si apoi dupa nume
        input:
            - rental1 (list)
            - rental2 (list)
        output:
            ---
        return:
            - True / False (bool)
        """

        book_id1 = rental1[0].get_book_id()
        book_id2 = rental2[0].get_book_id()

        client_id1 = rental1[0].get_client_id()
        client_id2 = rental2[0].get_client_id()

        if self.get_title_by_id(book_id1) == self.get_title_by_id(book_id2):
            return self.get_name_by_id(client_id1)  < self.get_name_by_id(client_id2)
        return self.get_title_by_id(book_id1) < self.get_title_by_id(book_id2)

    def sort_by_title_name(self):
        """
        functie care returneaza lista de rentals sortata dupa titlu si nume
        input:
            ---
        output:
            ---
        return:
            - ans (list de Rentals)
        """

        ans = Sort(self.cmp, self.key)
        return ans.gnome_sort(self.__repo.get_all_rentals())