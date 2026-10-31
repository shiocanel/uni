from datetime import datetime

from domain.validation_exception import ValidationException

class AutomobilValidator:
    def __init__(self, automobil):
        self.__automobil = automobil

    def validate(self):
        self.validate_id()
        self.validate_denumire()
        self.validate_pret()
        self.validate_model()
        self.validate_data()

    def validate_id(self):
        if self.__automobil.get_id() < 0:
            raise ValidationException("<<Invalid Id>>")
    
    def validate_denumire(self):
        if self.__automobil.get_denumire() == "":
            raise ValidationException("<<Invalid Denumire>>")

    def validate_pret(self):
        if self.__automobil.get_pret() < 0:
            raise ValidationException("<<Invalid Pret>>")
    
    def validate_model(self):
        if self.__automobil.get_model() == "":
            raise ValidationException("<<Invalid Model>>")
    
    def validate_data(self):
        try:
            datetime.strptime(self.__automobil.get_data(), "%d-%m-%Y").date()
        except TypeError:
            raise ValidationException("<<Invalid date>>")