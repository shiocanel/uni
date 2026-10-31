class Automobil:
    def __init__(self, id, denumire, pret, model, data):
        self.__data = {
            "id" : id,
            "denumire" : denumire,
            "pret" : pret,
            "model" : model,
            "data" : data
        }

    def get_id(self):
        return self.__data["id"]

    def get_denumire(self):
        return self.__data["denumire"]

    def get_pret(self):
        return self.__data["pret"]
    
    def get_model(self):
        return self.__data["model"]
    
    def get_data(self):
        return self.__data["data"]
    
    def set_id(self, id):
        self.__data["id"] = id

    def set_denumire(self, denumire):
        self.__data["denumire"] = denumire

    def set_pret(self, pret):
        self.__data["pret"] = pret
    
    def set_model(self, model):
        self.__data["model"] = model
    
    def set_data(self, data):
        self.__data["data"] = data