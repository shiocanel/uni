from repository.repository_exception import RepositoryException

from domain.validators.student_validator import StudentValidator
from domain.validators.subject_validator import SubjectValidator

from domain.student import Student
from domain.subject import Subject

class Repository:
    def __init__(self):
        self.__students = []
        self.__subjects = []

        self.load_students()
        self.load_subjects()

    def load_students(self):
        with open("D:\\uni\\fp\\examen1\\data\\students.txt", "r") as file:
            for line in file:
                parts = line.split(",")

                id, name, surname = parts[0].strip(), parts[1].strip(), parts[2].strip()
                
                student = Student(int(id), name, surname)
                StudentValidator(student).validate()
                self.add_student(student)
    
    def load_subjects(self):
        with open("D:\\uni\\fp\\examen1\\data\\subjects.txt", "r") as file:
            for line in file:
                parts = line.split(",")

                id, name, teacher = parts[0].strip(), parts[1].strip(), parts[2].strip()
                
                subject = Subject(int(id), name, teacher)
                SubjectValidator(subject).validate()
                self.add_subject(subject)


    def save_data(self):
        with open("D:\\uni\\fp\\examen1\\data\\students.txt", "w") as file:
            for item in self.__students:
                file.write(f"{item.get_id()}, {item.get_name()}, {item.get_surname()}\n")

        with open("D:\\uni\\fp\\examen1\\data\\subjects.txt", "w") as file:
            for item in self.__subjects:
                file.write(f"{item.get_id()}, {item.get_name()}, {item.get_teacher()}\n")

    def check_unique_subject(self, subject):
        for local_subject in self.__subjects:
            if local_subject.get_id() == subject.get_id():
                raise RepositoryException("<<Idential Ids>>")
                
    def add_subject(self, subject):
        self.check_unique_subject(subject)
        self.__subjects.append(subject)
        
        self.save_data()
    
    def update_subject(self, subject):
        for local_subject in self.__subjects:
            if local_subject.get_id() == subject.get_id():
                local_subject.set_name(subject.get_name())
                local_subject.set_surname(subject.get_surnmae())

                self.save_data()
                return
            
        raise RepositoryException("<<Id does not exist>>")
    
    def delete_subject(self, subject_id):
        for subject in self.__subjects:
            if subject.get_id() == subject_id:
                self.__subjects.remove(subject)

                self.save_data()
                return
            
        raise RepositoryException("<<Id does not exist>>>")
    
    def get_all_subjects(self):
        return self.__subjects

    def check_unique_students(self, student):
        for local_student in self.__students:
            if local_student.get_id() == student.get_id():
                raise RepositoryException("<<Idential Ids>>")
                
    def add_student(self, student):
        self.check_unique_students(student)
        self.__students.append(student)
        self.save_data()
    
    def update_student(self, student):
        for local_student in self.__students:
            if local_student.get_id() == student.get_id():
                local_student.set_name(student.get_name())
                local_student.set_surname(student.get_surnmae())

                self.save_data()
                return
            
        raise RepositoryException("<<Id does not exist>>")
    
    def delete_student(self, student_id):
    
        for student in self.__students:
            if student.get_id() == student_id:
                self.__students.remove(student)

                self.save_data()
                return
            
        raise RepositoryException("<<Id does not exist>>>")
    
    def get_all_students(self):
        return self.__students

