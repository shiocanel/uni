class Rental:
    def __init__(self, id, book_id, client_id):
        """
        constructor de initializare al unui rental
        input:
            - id (int)
            - book_id (int)
            - client_id (int)
        output:
            ---
        return:
            ---
        """

        self.__data = {
            "id" : id,
            "book_id" : book_id,
            "client_id" : client_id
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
    
    def get_book_id(self):
        """
        functie de get-er pentru a returna book_id-ul
        input:
            ---
        output:
            ---
        return:
            - book_id (int)
        """

        return self.__data["book_id"]
    
    def get_client_id(self):
        """
        functie de get-er pentru a returna client_id-ul
        input:
            ---
        output:
            ---
        return:
            - client_id (int)
        """

        return self.__data["client_id"]
    
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

    def set_book_id(self, value):
        """
        functie de set-er pentru a modifica book_id-ul
        input:
            - value (int)
        output:
            ---
        return:
            ---
        """

        self.__data["book_id"] = value
    
    def set_client_id(self, value):
        """
        functie de set-er pentru a modifica client_id-ul
        input:
            - value (int)
        output:
            ---
        return:
            ---
        """

        self.__data["client_id"] = value