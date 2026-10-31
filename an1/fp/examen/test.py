from domain.melodie import Melodie
from domain.melodii_validator import MelodiiValidator
from domain.validation_exception import ValidationException

from repository.repository import Repository
from repository.repository_exception import RepositoryException

from controller.melodii_service import MelodiiService

class Test:
    def __init__(self):
        pass
    
    def test(self):
        self.test_melodie()
        self.test_melodii_validator()
        self.test_repository()
        self.test_melodii_service()

        print("Au trecut toate testele!!!")

    def test_melodie(self):
        melodie = Melodie(1, "Raise", "Jayz", "Rock", "10.10.2026")

        assert melodie.get_id() == 1
        assert melodie.get_titlu() == "Raise"
        assert melodie.get_artist() == "Jayz"
        assert melodie.get_gen() == "Rock"
        assert melodie.get_data() == "10.10.2026"

        melodie.set_id(20)
        melodie.set_data("9.11.2011")

        assert melodie.get_id() == 20
        assert melodie.get_data() == "9.11.2011"

    def test_melodii_validator(self):
        melodie = Melodie(1, "Raise", "Jayz", "Rock", "10.10.2026")
        try:
            MelodiiValidator(melodie).validate()
            assert True
        except ValidationException:
            assert False


        melodie = Melodie(-10, "Raise", "Jayz", "Rock", "10.10.2026")
        try:
            MelodiiValidator(melodie).validate()
            assert False
        except ValidationException as ex:
            assert ex.get_message() == "<<Invalid Id>>"

        melodie = Melodie(2, "", "Jayz", "Rock", "10.10.2026")
        try:
            MelodiiValidator(melodie).validate()
            assert False
        except ValidationException as ex:
            assert ex.get_message() == "<<Invalid Titlu>>"

        melodie = Melodie(2, "Raise", "Jayz", "Rock", "10/10/2026")
        try:
            MelodiiValidator(melodie).validate()
            assert False
        except ValidationException as ex:
            assert ex.get_message() == "<<Invalid Data Format>>"

        
        melodie = Melodie(2, "Raise", "Jayz", "Rock", "100.10.2026")
        try:
            MelodiiValidator(melodie).validate()
            assert False
        except ValidationException as ex:
            assert ex.get_message() == "<<Invalid Data>>"

    def test_repository(self):
        repo = Repository()

        assert len(repo.get_all_melodii()) != 0

        melodie = Melodie(200, "Raise", "Jayz", "Rock", "10.10.2026")
        try:
            repo.add_melodie(melodie)
            repo.delete_melodie(melodie)
        except RepositoryException:
            assert False
        
        melodie = Melodie(1, "Raise", "Jayz", "Rock", "10.10.2026")
        try:
            repo.update_melodie(melodie)
            assert True
        except RepositoryException as ex:
            assert ex.get_message() == "<<Id does not exist>>"



    def test_melodii_service(self):
        service = MelodiiService(Repository())

        assert service.exista_melodie("dfnknfdjds", "sisdfjhfdsiuhf") == False
        assert service.exista_melodie("Raise", "Jayz") == True

        veche, noua = service.get_veche_noua()

        assert veche != noua

        