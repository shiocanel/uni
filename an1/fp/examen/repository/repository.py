from domain.melodie import Melodie
from domain.melodii_validator import MelodiiValidator
from domain.validation_exception import ValidationException

from repository.repository_exception import RepositoryException

import random

class Repository:
    def __init__(self):
        """
        functie de constructor pentru a initializa lista de melodii
        input:
            ---
        output:
            ---
        return:
            ---
        """

        self.__melodii = []

        self.load_melodii()

    def load_melodii(self):
        """
        functie care citeste din fisier melodiile
        input:
            ---
        output:
            ---
        return:
            ---
        """

        with open("D:\\uni\\fp\\examen\\data\\melodii.txt", "r") as file:
            for line in file:
                parts = line.split(",")

                id, titlu, artist, gen, data = parts[0].strip(), parts[1].strip(), parts[2].strip(), parts[3].strip(), parts[4].strip()

                melodie = Melodie(int(id), titlu, artist, gen, data)
                MelodiiValidator(melodie).validate()
                
                self.__melodii.append(melodie)

    def save_melodii(self):
        """
        functie care salveaza in fisier melodiile
        input:
            ---
        output:
            ---
        return:
            ---
        """

        with open("D:\\uni\\fp\\examen\\data\\melodii.txt", "w") as file:
            for item in self.__melodii:
                file.write(f"{item.get_id()}, {item.get_titlu()}, {item.get_artist()}, {item.get_gen()}, {item.get_data()}\n")

    def check_unique(self, melodie):
        """
        functie care verifica daca aceasta melodie este deja in lista
        input:
            - melodie (Melodie)
        output:
            - <<Identical Ids>> (daca exista)
        return:
            ---
        """

        for item in self.__melodii:
            if item.get_id() == melodie.get_id():
                raise RepositoryException("<<Identical Ids>>")

    def add_melodie(self, melodie):
        """
        functie care adauga in lista o melodie
        input:
            - melodie (Melodie)
        output:
            ---
        return:
            ---
        """

        try:
            self.check_unique(melodie)
            self.__melodii.append(melodie)

            self.save_melodii()
        except RepositoryException as ex:
            print(ex.get_message())

    def update_melodie(self, melodie):
        """
        functie care modifica o melodie dupa id
        input:
            - melodie (Melodie)
        output:
            ---
        return:
            ---
        """

        try:
            for item in self.__melodii:
                if item.get_id() == melodie.get_id():
                    item.set_titlu(melodie.get_titlu())
                    item.set_artist(melodie.get_artist())
                    item.set_gen(melodie.get_gen())
                    item.set_data(melodie.get_data())

                    self.save_melodii()
                    return
            raise RepositoryException("<<Id does not exist>>")
        except RepositoryException as ex:
            print(ex.get_message())

    def delete_melodie(self, melodie):
        self.__melodii.pop()
        self.save_melodii()

    def get_all_melodii(self):
        """
        functie care returneaza toate melodiile
        input:
            ---
        output:
            ---
        return:
            - melodii (list)
        """

        return self.__melodii
    
    def generate(self, x, lista_titlu, lista_artisti):
        """
        functie care genereaza random x meldoii, danduse o lista de titlu si de artsiti
        input:
            - x (int)
            - lista_titlu (list)
            - lista_artisti (list)
        output:
            ---
        return:
            ---
        """

        while x > 0:
            try:
                id = random.randint(0, 1001)
                titlu = random.choice(lista_titlu)
                artist = random.choice(lista_artisti)
                gen = random.choice(["Rock", "Pop", "Jazz"])
                zi = random.randint(1, 31)
                luna = random.randint(1, 12)
                an = random.randint(1, 2025)

                data = str(zi) + "." + str(luna) + "." + str(an)

                melodie = Melodie(id, titlu, artist, gen, data)
                MelodiiValidator(melodie).validate()
                self.add_melodie(melodie)
                
                x -= 1
            except ValidationException as ex:
                print(ex.get_message())
