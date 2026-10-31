from domain.validators.validation_exception import ValidationException

class StudentValidator:
    def __init__(self, student):
        self.__student = student

    def validate(self):
        self.validate_id()
        self.validate_name()
        self.validate_surname()

    def validate_id(self):
        if self.__student.get_id() < 0:
            raise ValidationException("<<Invalid Id>>")

    def validate_name(self):
        if self.__student.get_name() == "":
            raise ValidationException("<<Invalid name>>")
        
    def validate_surname(self):
        if self.__student.get_surname() == "":
            raise ValidationException("<<Invalid surname>>")
