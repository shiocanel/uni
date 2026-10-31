
class ValidationException(Exception):
    def __init__(self, message):
        """
        constructor de initializare al unui mesaj de exceptie
        input:
            - message (string)
        output:
            ---
        return:
            ---
        """

        self.__message = message

    def get_message(self):
        """
        functie care returneaza mesajul salva anterior
        input:
            ---
        output:
            ---
        return:
            - message (string)
        """
        
        return self.__message   
