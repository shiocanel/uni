from domain.validators.validation_exception import ValidationException

class ClientValidator:
    def __init__(self, client):
        self.__client = client

    def validate(self):
        self.validate_id()
        self.validate_name()
        self.validate_cnp()

    def validate_id(self):
        if self.__client.get_id() < 0:
            raise ValidationException("<<INVALID ID>>") 
    
    def validate_name(self):
        if self.__client.get_name() == "":
            raise ValidationException("<<INVALID NAME>>")
        
        nr = "1234567890"

        for cifra in nr:
            if cifra in self.__client.get_name():
                raise ValidationException("<<INVALID NAME>>")

    def validate_cnp(self):
        nr = "1234567890"

        for chr in self.__client.get_cnp():
            if chr not in nr:
                raise ValidationException("<<INVALID CNP>>")
