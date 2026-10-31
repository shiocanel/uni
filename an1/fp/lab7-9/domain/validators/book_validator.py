from domain.validators.validation_exception import ValidationException

class BookValidator:
    def __init__(self, book):
        """
        constructor de initializare a unei carti
        input:
            - book (Book)
        output:
            ---
        return:
            ---
        """

        self.__book = book

    def validate(self):
        """
        functie in care validam toti parametrii cartii
        input:
            ---
        output:
            ---
        return:
            ---
        """

        self.validate_id() 
        self.validate_title()
        self.validate_description()
        self.validate_author()       

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

        if self.__book.get_id() < 0:
            raise ValidationException("<<Invalid ID>>")

    def validate_title(self):
        """
        functie in care validam titlu in caz ca este vid
        input:
            ---
        output:
            ---
        return:
            ---
        """

        if self.__book.get_title() == "":
            raise ValidationException("<<Invalid title>>")
    
    def validate_description(self):
        """
        functie in care validam descrierea in caz ca este vid
        input:
            ---
        output:
            ---
        return:
            ---
        """

        if self.__book.get_description() == "":
            raise ValidationException("<<Invalid description>>")    

    def validate_author(self):
        """
        functie in care validam autorul in caz ca este vid
        input:
            ---
        output:
            ---
        return:
            ---
        """

        if self.__book.get_author() == "":
            raise ValidationException("<<Invalid author>>")