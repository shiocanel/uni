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
        nr = "1234567890"

        for n in nr:
            if n in self.__client.get_name():
                raise ValidationException("<<INVALID NAME>>")
            
    def validate_cnp(self):
        # if len(self.__client.get_cnp()) != 12:
            # raise ValidationException("<<INVALID CNP>>")
        ...