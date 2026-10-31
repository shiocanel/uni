from domain.validators.validation_exception import ValidationException

class ClientValidator:
    def __init__(self, client):
        """
        constructor de initializare a unui client
        input:
            - client (Client)
        output:
            ---
        return:
            ---
        """

        self.__client = client

    def validate(self):
        """
        functie in care validam toti parametrii clientului
        input:
            ---
        output:
            ---
        return:
            ---
        """

        self.validate_id()
        self.validate_name()
        self.validate_cnp()

    def validate_id(self):
        """
        functie in care validam id-ul in caz ca este negativ
        input:
            ---
        output:
            ---
        return:
            ---
        """

        if self.__client.get_id() < 0:
            raise ValidationException("<<Invalid ID>>")
            
    def validate_name(self):
        """
        functie in care validam daca numele are cifre sau este vid
        input:
            ---
        output:
            ---
        return:
            ---
        """

        for c in "1234567890":
            if c in self.__client.get_name():
                raise ValidationException("<<Invalid name>>")
        if self.__client.get_name() == "":
            raise ValidationException("<<Invalid name>>")

    def validate_cnp(self):
        """
        functie in care validam cnp-ul conform regulilor de pe wiki :)
        input:
            ---
        output:
            ---
        return:
            ---
        """

        cnp = self.__client.get_cnp()

        if len(cnp) != 13 or not cnp.isdigit():
            raise ValidationException("<<Invalid CNP>>")

        s = int(cnp[0])
        an = int(cnp[1:3])
        luna = int(cnp[3:5])
        zi = int(cnp[5:7])
        judet = int(cnp[7:9])

        if s in [1, 2]:
            anul = 1900 + an
        elif s in [3, 4]:
            anul = 1800 + an
        elif s in [5, 6]:
            anul = 2000 + an
        else:
            raise ValidationException("<<Invalid CNP>>")

        from datetime import datetime
        try:
            datetime(anul, luna, zi)
        except ValueError:
            raise ValidationException("<<Invalid CNP>>")

        if not (1 <= judet <= 52):
            raise ValidationException("<<Invalid CNP>>")
