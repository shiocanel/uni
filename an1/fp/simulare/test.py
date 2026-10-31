from domain.client import Client

from domain.validators.client_validator import ClientValidator

from domain.validators.validation_exception import ValidationException
from repository.repository_exception import RepositoryException
from repository.repository import Repository

from controller.service_client import ServiceClient

class Test:
    def __init__(self):
        pass
    
    def test(self):
        self.test_service_client()
        self.test_client_validator()
        # self.test_validaton_exception()
        self.test_client()

        self.test_repository_clients()
        
        print("<<ALL TESTS PASSED>>")


    def test_repository_clients(self):
        repo = Repository()

        clients = repo.get_all_clients()
        assert len(clients) == 5
        assert clients[0].get_name() == "Ioan"
        assert clients[-1].get_name() == "Stefan"

        new_client = Client(100, "Mihai", "1981215467894")
        ClientValidator(new_client).validate()
        repo.add_client(new_client)

        assert len(repo.get_all_clients()) == 6
        assert repo.get_all_clients()[-1].get_name() == "Mihai"

        dup_id_client = Client(100, "Altul", "1991215467894")
        try:
            repo.add_client(dup_id_client)
        except RepositoryException as msg:
            assert str(msg) == "<<Identical IDs>>"

        dup_cnp_client = Client(200, "Andrei", "1981215467894")
        try:
            repo.add_client(dup_cnp_client)
        except RepositoryException as msg:
            assert str(msg) == "<<Identical CNPs>>"

        updated_client = Client(100, "Mihai Alexandru", "1981215467894")
        repo.update_client(updated_client)

        all_clients = repo.get_all_clients()
        assert all_clients[-1].get_name() == "Mihai Alexandru"

        not_found_client = Client(999, "Ion", "1990101333444")
        try:
            repo.update_client(not_found_client)
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

        repo.delete_client(100)
        all_clients = repo.get_all_clients()
        assert len(all_clients) == 5
        assert all(client.get_id() != 100 for client in all_clients)

        try:
            repo.delete_client(999)
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

    def test_client(self):
        client = Client(1, "Mihai", "5010101221144")
        assert client.get_id() == 1
        assert client.get_name() == "Mihai"
        assert client.get_cnp() == "5010101221144"

        client.set_id(2)
        client.set_name("Andrei")
        client.set_cnp("6020201333444")

        assert client.get_id() == 2
        assert client.get_name() == "Andrei"
        assert client.get_cnp() == "6020201333444"

    def test_service_client(self):
        self.test_add_client()
        self.test_update_client()
        self.test_delete_client()

    def test_delete_client(self):
        repo = Repository()
        service = ServiceClient(repo)

        initial_length = len(repo.get_all_clients())

        service.delete_client(1)
        assert len(repo.get_all_clients()) == initial_length - 1

        try:
            service.delete_client(9999)
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

    def test_add_client(self):
        repo = Repository()
        service = ServiceClient(repo)

        service.add_client(1001, "Mihai", "1971215467894")
        assert len(repo.get_all_clients()) == 6
        assert repo.get_all_clients()[5].get_name() == "Mihai"

        try:
            service.add_client(1001, "Marcel", "1971215467894")
        except RepositoryException as msg:
            assert str(msg) == "<<Identical IDs>>"

        try:
            service.add_client(2000, "Ionel", "1971215467894")
        except RepositoryException as msg:
            assert str(msg) == "<<Identical CNPs>>"

    def test_update_client(self):
        repo = Repository()
        service = ServiceClient(repo)

        service.update_client(1, "Ionel", "6051218123457")
        assert repo.get_all_clients()[0].get_name() == "Ionel"
        assert repo.get_all_clients()[0].get_cnp() == "6051218123457"

        try:
            service.update_client(9999, "Andrei", "5031219222231")
        except RepositoryException as msg:
            assert str(msg) == "<<ID does not exist>>"

        try:
            service.update_client(1, "Ionfsdjsdk", "6051218123457")
        except RepositoryException as msg:
            assert str(msg) == "<<Identical CNPs>>"

    def test_client_validator(self):
        client = Client(1, "Ion", "5010101221144")
        try:
            ClientValidator(client).validate()
        except ValidationException as msg:
            raise ValidationException(msg)

        client = Client(-1, "Ion Popescu", "5010101221144")
        try:
            ClientValidator(client).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid ID>>"

        client = Client(2, "Ion123", "5010101221144")
        try:
            ClientValidator(client).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid name>>"

        client = Client(3, "", "5010101221144")
        try:
            ClientValidator(client).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid name>>"

        client = Client(4, "Maria", "123")
        try:
            ClientValidator(client).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid CNP>>"

        client = Client(5, "Andrei", "1960239460018")
        try:
            ClientValidator(client).validate()
        except ValidationException as msg:
            assert str(msg) == "<<Invalid CNP>>"

    def test_load_and_save_clients(self):
        repo = Repository()
        clients = repo.get_all_clients()

        assert len(clients) >= 5
        assert clients[0].get_name() == "Ioan"

        og_name = clients[0].get_name()
        clients[0].set_name("Ion Test")
        repo.save_clients()

        repo2 = Repository()
        assert repo2.get_all_clients()[0].get_name() == "Ion Test"

        repo2.get_all_clients()[0].set_name(og_name)
        repo2.save_clients()