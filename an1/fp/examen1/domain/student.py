class Student:
    def __init__(self, id, name, surname):
        self.__data = {
            "id" : id,
            "name" : name,
            "surname" : surname
        }

    def get_id(self):
        return self.__data["id"]

    def get_name(self):
        return self.__data["name"]

    def get_surname(self):
        return self.__data["surname"]
    
    def set_id(self, id):
        self.__data["id"] = id

    def set_name(self, name):
        self.__data["name"] = name
    
    def set_surname(self, surname):
        self.__data["surname"] = surname
        