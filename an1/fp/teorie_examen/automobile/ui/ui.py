from repository.repository_exception import RepositoryException
from domain.validation_exception import ValidationException

class UI:
    def __init__(self, service):
        self.__service = service

    def read(self, expected_type, message):
        while True:
            try:
                data = expected_type(input(message))
                return data
            except ValueError:
                print("<<Invalid Data>>")

    def start(self):
        while True:
            print("==Menu==")
            print("1. Add automobil")
            print("2. Update Automobil")
            print("3. Delete Automobil")
            print("4. See All Automobile")
            print("==Menu==")
            option = self.read(str, "Option: ")

            if option == "1":
                try:
                    id = self.read(int, "Id: ")
                    denumire = self.read(str, "Denumire: ")
                    pret = self.read(int, "Pret: ")
                    model = self.read(str, "Model: ")
                    data = self.read(str, "Data: ")
                    self.__service.add_automobil(id, denumire, pret, model, data)
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            
            elif option == "2":
                try:
                    id = self.read(int, "Id: ")
                    denumire = self.read(str, "Denumire: ")
                    pret = self.read(int, "Pret: ")
                    model = self.read(str, "Model: ")
                    data = self.read(str, "Data: ")
                    self.__service.update_automobil(id, denumire, pret, model, data)
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())

            elif option == "3":
                try:
                    id = self.read(int, "Id: ")
                    self.__service.delete_automobil(id, denumire, pret, model, data)
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())

            elif option == "4":
                try:
                    print("==Automobile==")
                    for automobil in self.__service.get_all_automobile():
                        print()
                        print(f"Id: {automobil.get_id()}")
                        print(f"Denumire: {automobil.get_denumire()}")
                        print(f"Pret: {automobil.get_pret()}")
                        print(f"Model: {automobil.get_model()}")
                        print(f"Data: {automobil.get_data()}")
                        print()
                    print("==Automobile==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "5":
                print("==Filrare==")
                text = self.read(str, "Text: ")
                perioada = self.read(int, "Numar de zile: ") 
                filtrat = self.__service.filtreaza(text, perioada)  
                
                print("==Automobile Filtrate==")
                for automobil in filtrat:
                    print()
                    print(f"Id: {automobil.get_id()}")
                    print(f"Denumire: {automobil.get_denumire()}")
                    print(f"Pret: {automobil.get_pret()}")
                    print(f"Model: {automobil.get_model()}")
                    print(f"Data: {automobil.get_data()}")
                    print()
                print("==Automobil Filtrate==")
            elif option == "6":
                print("Undo")
                self.__service.undo()                              
            else:
                print("Sa fie cu sanatate!!!")
                break        