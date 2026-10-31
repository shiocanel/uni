from domain.melodie import Melodie
from domain.melodii_validator import MelodiiValidator

from datetime import datetime

class MelodiiService:
    def __init__(self, repo):
        """
        functie de constructor care initializeaza repo
        input:
            - repo (Repository)
        output:
            ---
        return:
            ---
        """

        self.__repo = repo

    def add_melodie(self, id, titlu, artist, gen, data):
        """
        functie care adauga o melodie in repo
        input:
            - id (int)
            - titlu (string)
            - artist (string)
            - gen (string)
            - data (string) (dd.mm.yyyy)
        output:
            ---
        return:
            ---
        """

        melodie = Melodie(id, titlu, artist, gen, data)
        MelodiiValidator(melodie).validate()

        self.__repo.add_melodie(melodie)

    def update_melodie(self, id, titlu, artist, gen, data):
        """
        functie care modifica o melodie dupa id
        input:
            - id (int)
            - titlu (string)
            - artist (string)
            - gen (string)
            - data (string) (dd.mm.yyyy)
        output:
            ---
        return:
            ---
        """

        melodie = Melodie(id, titlu, artist, gen, data)
        MelodiiValidator(melodie).validate()

        self.__repo.update_melodie(melodie)

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

        return self.__repo.get_all_melodii()

    def exista_melodie(self, titlu, artist):
        for item in self.__repo.get_all_melodii():
            if item.get_titlu() == titlu and item.get_artist() == artist:
                return True
            
        return False

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

        self.__repo.generate(x, lista_titlu, lista_artisti)

    def get_veche_noua(self):
        """
        functie care returneaza cea mai veche si cea mai nou melodie dupa data
        input:
            ---
        output:
            ---
        return:
            - veche (Melodie)
            - noua (Melodie)
        """

        melodii = self.__repo.get_all_melodii()

        veche = melodii[0]
        noua = melodii[0]

        for item in melodii:
            text = item.get_data()
            parts = text.split(".")

            zi, luna, an = int(parts[0].strip()), int(parts[1].strip()), int(parts[2].strip())
            data1 = datetime(an, luna, zi)


            text = veche.get_data()
            parts = text.split(".")

            zi, luna, an = int(parts[0].strip()), int(parts[1].strip()), int(parts[2].strip())
            data2 = datetime(an, luna, zi)

            text = noua.get_data()
            parts = text.split(".")

            zi, luna, an = int(parts[0].strip()), int(parts[1].strip()), int(parts[2].strip())
            data3 = datetime(an, luna, zi)

            if data2 > data1:
                veche = item
            if data3 < data1:
                noua = item

        return veche, noua

    def get_nr_per_gen(self):
        """
        functie care numara cate melodii sunt per gen
        input:
            ---
        output:
            ---
        return:
            - ans (dict)
        """

        ans = {
            "Rock" : 0,
            "Pop" : 0,
            "Jazz" : 0
        }

        for item in self.__repo.get_all_melodii():
            ans[item.get_gen()] += 1

        return ans
    
    def get_cele_mai_popular(self):
        """
        functie care returneaza o lista cu cei mai populari artisti si cate melodii are (dupa melodii)
        input:
            ---
        output:
            ---
        return:
            - res (list)
        """
        
        ans = {}
        lista_artisti = []

        for item in self.__repo.get_all_melodii():
            lista_artisti.append(item.get_artist())

        for item in lista_artisti:
            ans[item] = 0
        
        for item in lista_artisti:
            ans[item] += 1

        mx = 0
        for item in ans:
            if ans[item] > mx:
                mx = ans[item]

        res = []
        for item in ans:
            if ans[item] == mx:
                res.append([item, ans[item]])

        return res
        