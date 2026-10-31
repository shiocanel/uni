from domain.TicTacToeStatus import TicTacToeStatus

class TicTacToeGame:
    def __init__(self, id, l0c0, l0c1, l0c2, l1c0, l1c1, l1c2, l2c0, l2c1, l2c2):
        self.__table = {
            "id" : id,
            "l0c0" : l0c0, 
            "l0c1" : l0c1, 
            "l0c2" : l0c2,
            "l1c0" : l1c0, 
            "l1c1" : l1c1, 
            "l1c2" : l1c2,
            "l2c0" : l2c0, 
            "l2c1" : l2c1, 
            "l2c2" : l2c2,
        }
    
    def get_TicTacToeStatus(self):
        return TicTacToeStatus(self.__table, "unfinished", "undefined")

    def get_id(self):
        return self.__table["id"]
    def get_l0c0(self):
        if self.__table["l0c0"] == "":
            return " "
        return self.__table["l0c0"]
    def get_l0c1(self):
        if self.__table["l0c1"] == "":
            return " "
        return self.__table["l0c1"]
    def get_l0c2(self):
        if self.__table["l0c2"] == "":
            return " "
        return self.__table["l0c2"]
    def get_l1c0(self):
        if self.__table["l1c0"] == "":
            return " "
        return self.__table["l1c0"]    
    def get_l1c1(self):
        if self.__table["l1c1"] == "":
            return " "
        return self.__table["l1c1"]
    def get_l1c2(self):
        if self.__table["l1c2"] == "":
            return " "
        return self.__table["l1c2"]
    def get_l2c0(self):
        if self.__table["l2c0"] == "":
            return " "
        return self.__table["l2c0"]
    def get_l2c1(self):
        if self.__table["l2c1"] == "":
            return " "
        return self.__table["l2c1"]    
    def get_l2c2(self):
        if self.__table["l2c2"] == "":
            return " "
        return self.__table["l2c2"]
        
    def set_id(self, value):
        self.__table["id"] = value
    def set_l0c0(self, value):
        self.__table["l0c0"] = value
    def set_l0c1(self, value):
        self.__table["l0c1"] = value
    def set_l0c2(self, value):
        self.__table["l0c2"] = value
    def set_l1c0(self, value):
        self.__table["l1c0"] = value 
    def set_l1c1(self, value):
        self.__table["l1c1"] = value
    def set_l1c2(self, value):
        self.__table["l1c2"] = value
    def set_l2c0(self, value):
        self.__table["l2c0"] = value
    def set_l2c1(self, value):
        self.__table["l2c1"] = value    
    def set_l2c2(self, value):
        self.__table["l2c2"] = value
