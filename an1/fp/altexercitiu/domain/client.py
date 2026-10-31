class Client:
    def __init__(self, id, name, cnp):
        self.__data = {
            "id" : id,
            "name" : name,
            "cnp" : cnp
        }

    def get_id(self):
        return self.__data["id"]
    
    def get_name(self):
        return self.__data["name"]
    
    def get_cnp(self):
        return self.__data["cnp"]
    
    def set_id(self, value):
        self.__data["id"] = value

    def set_name(self, value):
        self.__data["name"] = value
    
    def set_cnp(self, value):
        self.__data["cnp"] = value