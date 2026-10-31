from repository.repository_exception import RepositoryException
from domain.validation_exception import ValidationException

class UI:
    def __init__(self, service):
        """
        functie de constructor pentru a initializa service
        input:
            - service (Service)
        outpt:
            ---
        return:
            ---
        """

        self.__service = service

    def read(self, expected_type, text):
        """
        functie care citeste o data asteptandu-se un tip
        input:
            - expected_type (dataa_tyep)
            - text (string)
        output:
            ---
        return:
            - data (expected_type)
        """

        while True:
            try:
                data = expected_type(input(text))
                return data
            except ValueError:
                print("<<Invalid Data Type>>")

    def start(self):
        """
        functie care afiseaza menu
        input:
            - option (int)
        output:
            - menu
        return:
            ---
        """

        while True:
            print("==Menu==")           
            print("1. Modifica melodie")
            print("2. Trebuie sa existe o melodie cu")
            print("3. Creaza aleator melodii")
            print("4. Cea mai veche si cea mai noua melodie")
            print("5. Numarul de melodii pe gen")
            print("6. Artistul cu cele mai multe melodii")            
            print("0. Exit")
            print("==Menu==")           

            option = self.read(str, "Option: ")

            if option == "1":
                try:
                    id = self.read(int, "Id: ")
                    titlu = self.read(str, "Titlu: ")
                    artist = self.read(str, "Artist: ")
                    gen = self.read(str, "Gen: ")
                    data = self.read(str, "Data (dd.mm.yyyy): ")

                    self.__service.update_melodie(id, titlu, artist, gen, data)

                    print("Este modificat cu succes")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "2":
                try:
                    titlu = self.read(str, "Titlu: ")
                    artist = self.read(str, "Artist: ")

                    exista = self.__service.exista_melodie(titlu, artist)

                    if exista:
                        print("Exista astfel de melodie!!")
                    else:
                        print("Nu exista o astfel de melodie!!!")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())

            elif option == "3":
                try:
                    x = self.read(int, "Numarul de Melodii de generat: ")
                    lista_titlu = []
                    lista_artisti = []

                    nr_titlu = self.read(int, "Numarul de Titlu: ")
                    for i in range(nr_titlu):
                        print(f"Titlu {i + 1}: ", end="")
                        titlu = self.read(str, "")
                        lista_titlu.append(titlu)

                    nr_artisti = self.read(int, "Numarul de Artisti: ")
                    for i in range(nr_artisti):
                        print(f"Artist {i + 1}: ", end="")
                        artist = self.read(str, "")
                        lista_artisti.append(artist)

                    self.__service.generate(x, lista_titlu, lista_artisti)

                    print("Este generat cu succes")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            
            elif option == "4":
                try:
                    veche, noua = self.__service.get_veche_noua()

                    print("==Melodia cea mai veche==")
                    print(f"Id: {veche.get_id()}")
                    print(f"Titlu: {veche.get_titlu()}")
                    print(f"Artist: {veche.get_artist()}")
                    print(f"Gen: {veche.get_gen()}")
                    print(f"Data: {veche.get_data()}")
                    print()

                    print("==Melodia cea mai noua==")
                    print(f"Id: {noua.get_id()}")
                    print(f"Titlu: {noua.get_titlu()}")
                    print(f"Artist: {noua.get_artist()}")
                    print(f"Gen: {noua.get_gen()}")
                    print(f"Data: {noua.get_data()}")
                    print()
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            
            elif option == "5":
                try:
                    print("==Numarul de melodii per gen==")
                    ans = self.__service.get_nr_per_gen()

                    for item in ans:
                        print(item, ans[item])

                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())

            elif option == "6":
                try:
                    print("==Artistul cu cele mai multe melodii==")
                    
                    artisti_populari = self.__service.get_cele_mai_popular()

                    print("==Artisiti Populari==")
                    for artist in artisti_populari:
                        print()
                        print(f"Artist: {artist[0]}")
                        print(f"Numarul de melodii: {artist[1]}")
                        print()
                        
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())

            elif option == "0":
                print("Sa fie cu sanatate!")
                break
            else:
                print("Invalid Option")
        