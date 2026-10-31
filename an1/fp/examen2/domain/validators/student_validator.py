from domain.validators.validation_exception import ValidationException

class StudentValidator:
    def __init__(self, student):
        self.__student = student

    def validate(self):
        self.validate_id()
        self.validate_name()
        self.validate_group()

    def validate_id(self):
        if self.__student.get_id() <= 0:
            raise ValidationException("<<Student ID must be a positive integer>>")
        
    def validate_name(self): 
        if len(self.__student.get_name().strip()) == 0:
            raise ValidationException("<<Student name cannot be empty>>")
        
    def validate_group(self):    
        if self.__student.get_group() <= 0:
            raise ValidationException("<<Student group must be a positive integer>>")
    
