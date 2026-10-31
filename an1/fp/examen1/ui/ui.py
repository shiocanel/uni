from repository.repository_exception import RepositoryException
from domain.validators.validation_exception import ValidationException

class UI:
    def __init__(self, student_service, subject_service):
        self.__student_service = student_service
        self.__subject_service = subject_service

    def read(self, expected_type, message):
        data = input(message)
        
        try:
            data = expected_type(data)
            return data
        except ValueError:
            print("<<Invalid data type>>")

    def start(self):
        while True:
            print("===Menu===")
            print("1. Manage Students")
            print("2. Manage Subjects")
            print("0. Exit")
            print("===Menu===")

            option = self.read(str, "Option: ")

            if option == "1":
                self.manage_students()
            elif option == "2":
                self.manage_subjects()
            elif option == "0":
                print("Sa fie cu bine!")
                break
            else:
                print("<<We do not have such option, please try again>>")

    def manage_students(self):
        while True:
            print("===Students===")
            print("1. Add Students")
            print("2. Update Students")
            print("3. Delete Students")
            print("4. See All Students")
            print("0. Exit")
            print("===Students===")

            option = self.read(str, "Option: ")

            if option == "1":
                try:
                    id = self.read(int, "ID: ")
                    name = self.read(str, "Name: ")
                    surname = self.read(str, "Surname: ")
                    self.__student_service.add_student(id, name, surname)
                    print("==Student added succesfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "2":
                try:
                    id = self.read(int, "ID: ")
                    name = self.read(str, "Name: ")
                    surname = self.read(str, "Surname: ")
                    self.__student_service.update_student(id, name, surname)
                    print("==Student updated succesfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "3":
                try:
                    id = self.read(int, "ID: ")
                    self.__student_service.delete_student(id)
                    print("==Student deleted succesfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "4":
                try:
                    students = self.__student_service.get_all_students()

                    print("==All Students==")
                    for student in students:
                        print(f"Id: {student.get_id()}")
                        print(f"Name: {student.get_name()}")
                        print(f"Surname: {student.get_surname()}")
                        print()
                    print("==All Students==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "0":
                break
            else:
                print("<<We do not have such option, please try again>>")
                
    def manage_subjects(self):
        while True:
            print("===Subjects===")
            print("1. Add Subjects")
            print("2. Update Subjects")
            print("3. Delete Subjects")
            print("4. See All Subjects")
            print("0. Exit")
            print("===Subjects===")

            option = self.read(str, "Option: ")

            if option == "1":
                try:
                    id = self.read(int, "ID: ")
                    name = self.read(str, "Name: ")
                    teacher = self.read(str, "Teacher: ")
                    self.__subject_service.add_subject(id, name, teacher)
                    print("==Subject added succesfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "2":
                try:
                    id = self.read(int, "ID: ")
                    name = self.read(str, "Name: ")
                    teacher = self.read(str, "Teacher: ")
                    self.__subject_service.update_subject(id, name, teacher)
                    print("==Subject updated succesfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "3":
                try:
                    id = self.read(int, "ID: ")
                    self.__subject_service.delete_subject(id)
                    print("==Subject deleted succesfully==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "4":
                try:
                    subjects = self.__student_service.get_all_students()

                    print("==All Subjects==")
                    for subject in subjects:
                        print(f"Id: {subject.get_id()}")
                        print(f"Name: {subject.get_name()}")
                        print(f"Teacher: {subject.get_teacher()}")
                        print()
                    print("==All Subjects==")
                except (RepositoryException, ValidationException) as ex:
                    print(ex.get_message())
            elif option == "0":
                break
            else:
                print("<<We do not have such option, please try again>>")
