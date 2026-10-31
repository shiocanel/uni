from domain.validators.validation_exception import ValidationException

class RentalValidator:
    def __init__(self, rental):
        """
        constructor de initializare a unui rental
        input:
            - rental (Rental)
        output:
            ---
        return:
            ---
        """

        self.__rental = rental

    def validate(self):
        """
        functie in care validam toti parametrii rental-ului
        input:
            ---
        output:
            ---
        return:
            ---
        """

        self.validate_id()
        self.validate_book_id()
        self.validate_client_id()

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

        if self.__rental.get_id() < 0:
            raise ValidationException("<<Invalid ID>>")
            
    def validate_book_id(self):
        """
        functie in care validam id-ul in caz ca este negativ
        input:
            ---
        output:
            ---
        return:
            ---
        """

        if self.__rental.get_book_id() < 0:
            raise ValidationException("<<Invalid ID>>")
        
    def validate_client_id(self):
        """
        functie in care validam id-ul in caz ca este negativ
        input:
            ---
        output:
            ---
        return:
            ---
        """

        if self.__rental.get_client_id() < 0:
            raise ValidationException("<<Invalid ID>>")