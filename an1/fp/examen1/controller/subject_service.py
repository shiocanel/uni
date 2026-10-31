from domain.validators.subject_validator import SubjectValidator
from domain.subject import Subject

class SubjectService():
    def __init__(self, repo):
        self.__repo = repo

    def add_subject(self, id, name, teacher):
        subject = Subject(id, name, teacher)
        SubjectValidator(subject).validate()
        self.__repo.add_subject(subject)

    def update_subject(self, id, name, teacher):
        subject = Subject(id, name, teacher)
        SubjectValidator(subject).validate()
        self.__repo.update_subject(subject)
        
    def delete_subject(self, id):
        self.__repo.delete_subject(id)

    def get_all_subjects(self):
        return self.__repo.get_all_subjects()
