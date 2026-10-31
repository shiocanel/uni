from domain.validators.validation_exception import ValidationException

class SubjectValidator:
    def __init__(self, subject):
        self.__subject = subject

    def validate(self):
        self.validate_id()
        self.validate_name()
        self.validate_teacher()

    def validate_id(self):
        if self.__subject.get_id() < 0:
            raise ValidationException("<<Invalid Id>>")

    def validate_name(self):
        if self.__subject.get_name() == "":
            raise ValidationException("<<Invalid name>>")
        
    def validate_teacher(self):
        if self.__subject.get_teacher() == "":
            raise ValidationException("<<Invalid teacher>>")
