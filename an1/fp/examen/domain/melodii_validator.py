from domain.validation_exception import ValidationException

from datetime import datetime
class MelodiiValidator:
    def __init__(self, melodie):
        """
        functie de constructor pentru o melodie
        input:
            - melodie (Melodie)
        output:
            ---
        return:
            ---
        """

        self.__melodie = melodie

    def validate(self):
        """
        functie care valideaza datele
        input:
            ---
        output:
            ---
        return:
            ---
        """

        self.validate_id()
        self.validate_titlu()
        self.validate_artist()
        self.validate_gen()
        self.validate_data()

    def validate_id(self):
        """
        functie care valideaza id
        input:
            ---
        output:
            - <<Invalid Id>> (daca id < 0)
        return:
            ---
        """

        if self.__melodie.get_id() < 0:
            raise ValidationException("<<Invalid Id>>")
        
    def validate_titlu(self):
        """
        functie care valideaza titlul:
        input:
            ---
        output:
            - <<Invalid Titlu>> (daca este vid)
        return:
            ---
        """

        if self.__melodie.get_titlu() == "":
            raise ValidationException("<<Invalid Titlu>>")
        
    def validate_artist(self):
        """
        functie care valideaza artist:
        input:
            ---
        output:
            - <<Invalid Artist>> (daca este vid)
        return:
            ---
        """

        if self.__melodie.get_artist() == "":
            raise ValidationException("<<Invalid Artist>>")
        
    def validate_gen(self):
        """
        functie care valideaza gen:
        input:
            ---
        output:
            - <<Invalid Gen>> (daca este vid)
            - <<Genu Trebuie de tip 'Rock', 'Pop', 'Jazz'>>  (daca nu apartine unui gen stabilit)
        return:
            ---
        """

        if self.__melodie.get_gen() == "":
            raise ValidationException("<<Invalid Gen>>")
        if self.__melodie.get_gen() not in ["Rock", "Pop", "Jazz"]:
            raise ValidationException("<<Genu Trebuie de tip 'Rock', 'Pop', 'Jazz'>>")
    
    def validate_data(self):
        """
        functie care valideaza data
        input:
            ---
        output:
            - Invalid data format (daca nu este de froma dd.mm.yyyy)
            - Invalid data (daca aceata data nu exista)
        return:
            ---
        """
        text = self.__melodie.get_data()

        parts = text.split(".")

        if len(parts) != 3:
            raise ValidationException("<<Invalid Data Format>>")

        try:
            zi, luna, an = int(parts[0].strip()), int(parts[1].strip()), int(parts[2].strip())
            data = datetime(an, luna, zi)
        except ValueError:
            raise ValidationException("<<Invalid Data>>")
