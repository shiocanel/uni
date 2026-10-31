from domain.automobil import Automobil
from domain.automobil_validator import AutomobilValidator
from repository.repository_exception import RepositoryException

class Repository:
    def __init__(self):
        self.__automobile = []
        self.__undo = []

        self.load_automobile()

    def load_automobile(self):
        with open("D:\\uni\\fp\\teorie_examen\\automobile\\data\\data.txt", "r") as file:
            for line in file:
                parts = line.split(",")

                id, denumire, pret, model, data = parts[0].strip(), parts[1].strip(), parts[2].strip(), parts[3].strip(), parts[4].strip()

                print(id)
                automobil = Automobil(int(id), denumire, int(pret), model, data)
                
                AutomobilValidator(automobil).validate()
                self.__automobile.append(automobil)

    def save_automobile(self):
        lista = []
        for a in self.__automobile:
            lista.append(a)

        self.__undo.append(lista)
        with open("D:\\uni\\fp\\teorie_examen\\automobile\\data\\data.txt", "w") as file:
            for item in self.__automobile:
                file.write(f"{item.get_id()}, {item.get_denumire()}, {item.get_pret()}, {item.get_model()}, {item.get_data()}\n")

    def check_unique(self):
        for item1 in self.__automobile:
            for item2 in self.__automobile:
                if item1 != item2:
                    if item1.get_id() == item2.get_id():
                        raise RepositoryException("<<Duplicate Ids>>")

    def add_automobil(self, automobil):
        try:
            self.__automobile.append(automobil)
            self.check_unique()
            self.save_automobile()
        except RepositoryException as ex:
            print(ex.get_message())
            self.__automobile.pop()

    def update_automobil(self, automobil):
        for local_automobil in self.__automobile:
            if local_automobil.get_id() == automobil.get_id():
                local_automobil.set_denumire(automobil.get_denumire())
                local_automobil.set_pret(automobil.get_pret())
                local_automobil.set_model(automobil.get_automobil())
                local_automobil.set_data(automobil.get_data())

                self.save_automobile()
                return
            
        raise RepositoryException("<<Automobil does not exist>>")
    
    def delete_automobil(self, id):
        for local_automobil in self.__automobile:
            if local_automobil.get_id() == id:
                self.__automobile.remove(local_automobil)
                self.save_automobile()
                return
            
        raise RepositoryException("<<Automobil does not exist>>")

    def get_all_automobile(self):
        return self.__automobile
    
    def undo(self):
        self.__automobile = self.__undo[-1]
        self.__undo.pop()
