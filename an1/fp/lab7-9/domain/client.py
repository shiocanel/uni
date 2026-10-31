class Client:
    def __init__(self, id, name, cnp):
        """
        constructor de initializare al unui client
        input:
            - id (int)
            - name (string)
            - cnp (string)
        output:
            ---
        return:
            ---
        """

        self.__data = {
            "id": id,
            "name": name,
            "cnp": cnp
        }
        
    def get_id(self):
        """
        functie de get-er pentru a returna id-ul
        input:
            ---
        output:
            ---
        return:
            - id (int)
        """

        return self.__data["id"]
    
    def get_name(self):
        """
        functie de get-er pentru a returna name
        input:
            ---
        output:
            ---
        return:
            - name (string)
        """

        return self.__data["name"]
    
    def get_cnp(self):
        """
        functie de get-er pentru a returna cnp
        input:
            ---
        output:
            ---
        return:
            - cnp (string)
        """


        return self.__data["cnp"]
    
    def set_id(self, value):
        """
        functie de set-er pentru a modifica id-ul
        input:
            - value (int)
        output:
            ---
        return:
            ---
        """

        self.__data["id"] = value
    
    def set_name(self, value):
        """
        functie de set-er pentru a modifica name
        input:
            - value (string)
        output:
            ---
        return:
            ---
        """

        self.__data["name"] = value

    def set_cnp(self, value):
        """
        functie de set-er pentru a modifica cnp-ul
        input:
            - value (string)
        output:
            ---
        return:
            ---
        """

        self.__data["cnp"] = value
