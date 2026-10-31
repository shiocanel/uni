class Lab:
    def __init__(self, id, description, deadline):
        self.__data = {
            "id": id,
            "description": description,
            "deadline": deadline
        }

    def get_id(self):
        return self.__data["id"]

    def get_description(self):
        return self.__data["description"]

    def get_deadline(self):
        return self.__data["deadline"]

    def set_id(self, new_id):
        self.__data["id"] = new_id

    def set_description(self, new_description):
        self.__data["description"] = new_description

    def set_deadline(self, new_deadline):
        self.__data["deadline"] = new_deadline

    def __str__(self):
        return f"Lab ID: {self.get_id()}, Description: {self.get_description()}, Deadline: {self.get_deadline()}"