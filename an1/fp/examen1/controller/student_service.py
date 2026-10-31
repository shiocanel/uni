from domain.validators.student_validator import StudentValidator
from domain.student import Student

class StudentService:
    def __init__(self, repo):
        self.__repo = repo

    def add_student(self, id, name, surname):
        student = Student(id, name, surname)
        StudentValidator(student).validate()
        self.__repo.add_student(student)

    def update_student(self, id, name, surname):
        student = Student(id, name, surname)
        StudentValidator(student).validate()
        self.__repo.update_student(student)
    
    def delete_student(self, id):
        self.__repo.delete_student(id)

    def get_all_students(self):
        return self.__repo.get_all_students()