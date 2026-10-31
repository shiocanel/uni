class Melodie:
    def __init__(self, id, titlu, artist, gen, data):
        """
        functie de constructor pentru o melodie
        input:
            - id (int)
            - titlu (string)
            - artist (string)
            - gen (string)
            - data (string) (dd.mm.yyyy)
        output:
            ---
        return:
            ---
        """

        self.__data = {
            "id" : id,
            "titlu" : titlu,
            "artist" : artist,
            "gen" : gen,
            "data" : data
        }

    def get_id(self):
        """
        functie de get pentru a retruna id:
        input:
            ---
        output:
            ---
        return:
            - id (int) 
        """

        return self.__data["id"]
    
    def get_titlu(self):
        """
        functie de get pentru a retruna titlu:
        input:
            ---
        output:
            ---
        return:
            - titlu (string) 
        """

        return self.__data["titlu"]
    
    def get_artist(self):
        """
        functie de get pentru a retruna artist:
        input:
            ---
        output:
            ---
        return:
            - artist (string) 
        """

        return self.__data["artist"]
    
    def get_gen(self):
        """
        functie de get pentru a retruna gen:
        input:
            ---
        output:
            ---
        return:
            - gen (string) 
        """

        return self.__data["gen"]
    
    def get_data(self):
        """
        functie de get pentru a retruna data:
        input:
            ---
        output:
            ---
        return:
            - data (string) (dd.mm.yyyy) 
        """

        return self.__data["data"]
    
    def set_id(self, id):
        """
        functie de set pentru a modifica id:
        input:
            - id (int)
        output:
            ---
        return:
            ---
        """

        self.__data["id"] = id
    
    def set_titlu(self, titlu):
        """
        functie de set pentru a modifica titlu:
        input:
            - titlu (string)
        output:
            ---
        return:
            ---
        """

        self.__data["titlu"] = titlu

    def set_artist(self, artist):
        """
        functie de set pentru a modifica artist:
        input:
            - artist (string)
        output:
            ---
        return:
            ---
        """

        self.__data["artist"] = artist

    def set_gen(self, gen):
        """
        functie de set pentru a modifica gen:
        input:
            - gen (string)
        output:
            ---
        return:
            ---
        """

        self.__data["gen"] = gen

    def set_data(self, data):
        """
        functie de set pentru a modifica data:
        input:
            - data (string) (dd.mm.yyyy)
        output:
            ---
        return:
            ---
        """

        self.__data["data"] = data