from domain.automobil import Automobil
from domain.automobil_validator import AutomobilValidator

class ServiceAutomobil:
    def __init__(self, repo):
        self.__repo = repo

    def add_automobil(self, id, denumire, pret, model, data):
        automobil = Automobil(id, denumire, pret, model, data)
        AutomobilValidator(automobil).validate()
        self.__repo.add_automobil(automobil)

    def update_automobil(self, id, denumire, pret, model, data):
        automobil = Automobil(id, denumire, pret, model, data)
        AutomobilValidator(automobil).validate()
        self.__repo.update_automobil(automobil)
        
    def delete_automobil(self, id):
        self.__repo.delete_automobil(id)

    def get_all_automobile(self):
        return self.__repo.get_all_automobile()

    def compara(self, item, text, numar):
        return (text == "" or text in item.get_denumire()) and (numar == -1 or item.get_pret() <= numar) 

    def filtreaza(self, text, numar):
        filtrat = list(self.__repo.get_all_automobile())
        filtrat = list(filter(lambda item : self.compara(item, text, numar), filtrat))

        return filtrat
    
    def undo(self):
        self.__repo.undo()