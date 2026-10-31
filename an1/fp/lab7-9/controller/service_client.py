from domain.client import Client
from domain.validators.client_validator import ClientValidator
import random

class ServiceClient:
    def __init__(self, repository):
        """
        functie in care initializam repo
        input:
            - repository (Repository)
        output:
            ---
        return:
            ---
        """

        self.__repo = repository

    def add_client(self, id, name, cnp):
        """
        functie care adauga un client
        input:
            - id (int)
            - name (string)
            - cnp (string)
        output:
            ---
        return:
            ---
        """

        client = Client(id, name, cnp)
        ClientValidator(client).validate()
        self.__repo.add_client(client)

    def update_client(self, id, name, cnp):
        """
        functie care modifica un client
        input:
            - id (int)
            - name (string)
            - cnp (string)
        output:
            ---
        return:
            ---
        """

        client = Client(id, name, cnp)
        ClientValidator(client).validate()

        self.__repo.update_client(client)

    def delete_client(self, client_id):
        """
        functie care sterge un client
        input:
            - client_id (int)
        outpu:
            ---
        return:
            ---
        """

        self.__repo.delete_client(client_id)

    def see_all_clients(self):
        """
        functie care returneaza toti clientii
        input:
            ---
        output:
            ---
        return:
            - lista de clienti din repo
        """
        
        return self.__repo.get_all_clients()

    def generate(self, x):
        """
        functie care genereaza x clienti random (aproape)
        input:
            - x (int)
        output:
            ---
        return:
            ---
        """
        
        while(x):
            while(True):
                try:
                    sz = len(self.__repo.get_all_clients())
                    
                    id = sz + 1
                    name = random.choice(["Ioan", "Andrei", "Anton", "Maria", "Stefan", "Octavian", "Riccardo", "Marcel", "Alex"])
                    cnp = random.choice(["1740313077796", "1740313078608", "1740313070363", "1740313071648", "1740313079247", "1740313074045"])

                    client = Client(id, name, cnp)
                    ClientValidator(client).validate()
                    self.__repo.add_client(client)   
                    x -= 1
                    break
                except:
                    continue
                
    def save_clients(self):
        """
        functie care salveaza clientii intr-un fisier
        input:
            ---
        output:
            ---
        return:
            ---
        """
        

        self.__repo.save_clients()