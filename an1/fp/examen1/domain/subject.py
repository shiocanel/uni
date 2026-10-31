class Subject:
    def __init__(self, id, name, teacher):
        self.__data = {
            "id" : id,
            "name" : name,
            "teacher" : teacher
        }

    def get_id(self):
        return self.__data["id"]

    def get_name(self):
        return self.__data["name"]

    def get_teacher(self):
        return self.__data["teacher"]
    
    def set_id(self, id):
        self.__data["id"] = id
    
    def set_name(self, name):
        self.__data["name"] = name

    def set_teacher(self, teacher):
        self.__data["teacher"] = teacher