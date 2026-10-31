class Book:
    def __init__(self, id, title, description, author):
        """
        constructor de initializare a unei carti
        input:
            - id (int)
            - title (string)
            - description (string)
            - author (string)
        output:
            ---
        return:
            ---
        """

        self.__data = {
            "id": id,
            "title": title,
            "description": description,
            "author": author
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
    
    def get_title(self):
        """
        functie de get-er pentru a returna titlul
        input:
            ---
        output:
            ---
        return:
            - title (string)
        """

        return self.__data["title"]
    
    def get_description(self):
        """
        functie de get-er pentru a returna descrierea
        input:
            ---
        output:
            ---
        return:
            - descriprion (string)
        """

        return self.__data["description"]
    
    def get_author(self):
        """
        functie de get-er pentru a returna autorul
        input:
            ---
        output:
            ---
        return:
            - author (string)
        """

        return self.__data["author"]
    
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

    def set_title(self, value):
        """
        functie de set-er pentru a modifica titlu
        input:
            - value (string)
        output:
            ---
        return:
            ---
        """

        self.__data["title"] = value

    def set_description(self, value):
        """
        functie de set-er pentru a modifica descrierea
        input:
            - value (string)
        output:
            ---
        return:
            ---
        """

        self.__data["description"] = value

    def set_author(self, value):
        """
        functie de set-er pentru a modifica autorul
        input:
            - value (string)
        output:
            ---
        return:
            ---
        """

        self.__data["author"] = value