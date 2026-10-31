from domain.book import Book
from domain.validators.book_validator import BookValidator
import random

class ServiceBook:
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

    def add_book(self, id, title, description, author):
        """
        functie care adauga o carte
        input:
            - id (int)
            - title (string)
            - descriprion (string)
            - author (string)
        output:
            ---
        return:
            ---
        """

        book = Book(id, title, description, author)
        BookValidator(book).validate()
        self.__repo.add_book(book)


    def update_book(self, id, title, description, author):
        """
        functie care modifica o carte
        input:
            - id (int)
            - title (string)
            - descriprion (string)
            - author (string)
        output:
            ---
        return:
            ---
        """

        book = Book(id, title, description, author)
        BookValidator(book).validate()

        self.__repo.update_book(book)

    def delete_book(self, book_id):
        """
        functie care sterge o carte
        input:
            - book_id (int)
        outpu:
            ---
        return:
            ---
        """

        self.__repo.delete_book(book_id)

    def see_all_books(self):
        """
        functie care returneaza toate cartile
        input:
            ---
        output:
            ---
        return:
            - lista de books din repo
        """
        
        return self.__repo.get_all_books()

    def generate(self, x):
        """
        functie care genereaza x carti random (aproape)
        input:
            - x (int)
        output:
            ---
        return:
            ---
        """
        
        while(x):
            while(True):
                try:
                    sz = len(self.__repo.get_all_books())
                    
                    id = sz + 1
                    title = random.choice(["The Revised Technique", "Ballroom Dancing", "Popular Variations", "Leading Competition Figures: Waltz and Foxtrot", "Kristine M. McCusker, Diane Pecknold"])
                    
                    len_description = 20
                    description = ""
                    for i in range(len_description):
                        description += random.choice(['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'])

                    author = random.choice(["Edith Ballwebber", "August Harris & Donnabel Keys", "Alma Heaton", "Judy Patterson Wright", "Diane Jarmolow", "Rudi Trautz", "Thomas Hill"])

                    book = Book(id, title, description, author)
                    BookValidator(book).validate()
                    self.__repo.add_book(book)

                    x -= 1
                    break
                except:
                    continue
                
    def save_books(self):
        """
        functie care salveaza cartile intr-un fisier
        input:
            ---
        output:
            ---
        return:
            ---
        """
        
        self.__repo.save_books()