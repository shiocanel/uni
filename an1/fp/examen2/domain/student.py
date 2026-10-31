class Student:
    def __init__(self, id, name, group):
        self.__data = {
            "id" : id,
            "name" : name,
            "group" : group
        }

    def get_id(self):
        return self.__data["id"]
    
    def get_name(self): 
        return self.__data["name"]
    
    def get_group(self):    
        return self.__data["group"]

    def set_id(self, new_id):
        self.__data["id"] = new_id    
    
    def set_name(self, new_name):
        self.__data["name"] = new_name  
    
    def set_group(self, new_group):
        self.__data["group"] = new_group

    def __str__(self):
        return f"Student ID: {self.get_id()}, Name: {self.get_name()}, Group: {self.get_group()}"
