class ValidationException(Exception):
    def __init__(self, msg):
        """
        functie de constructor pentru a initializa un mesaj
        input:
            - msg (string)
        output:
            ---
        return:
            ---
        """

        self.__msg = msg

    def get_message(self):
        """
        functie care returneaza mesajul in caz de exceptie
        input:
            ---
        output:
            ---
        return:
            - msg (string)
        """
        
        return self.__msg