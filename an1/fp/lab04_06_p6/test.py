from pachet import *
from undo import undo

def test_program():
    """
    functie care ruleaza toate testele
    """
    test_pachet()
    # test_adaugare() nu pot
    # test_cautare() nu pot
    # test_citire() nu pot
    # test_filtrare() nu pot
    # test_rapoarte() nu pot
    # test_stergere() nu pot
    test_validare()
    test_undo()
    print("minunat")

def test_undo():
    pachete = []
    undo_list = []

    assert undo(pachete, undo_list, True) == False
    
    pachete.append(creaza_pachet(0, "Atena", "2025-07-18", "2025-08-03", 302))
    
    undo_list.append(pachete.copy())
    pachete.append(creaza_pachet(1, "Barcelona", "2025-08-22", "2025-08-30", 124))

    assert undo(pachete, undo_list, True) == True

    pachet_vechi = creaza_pachet(0, "Atena", "2025-07-18", "2025-08-03", 302)
    assert pachete == [pachet_vechi]


def test_validare():
    test_valideaza_id()
    test_valideaza_destinatia()
    test_valideaza_data()
    test_valideaza_datile()
    test_valideaza_pret()
    test_valideaza_date()

def test_valideaza_id():
    assert valideaza_id(0, True) == True
    assert valideaza_id(10, True) == True
    assert valideaza_id("10", True) == False
    assert valideaza_id(-5, True) == False

def test_valideaza_destinatia():
    assert valideaza_destinatia("Paris", True) == True
    assert valideaza_destinatia("", True) == False

def test_valideaza_data():
    assert valideaza_data_inceput("2025-10-28", True) == True
    assert valideaza_data_sfarsit("2025-12-31", True) == True
    assert valideaza_data_inceput("28-10-2025", True) == False
    assert valideaza_data_sfarsit("2025/12/31", True) == False

def test_valideaza_datile():
    assert valideaza_datile("2025-10-01", "2025-10-28", True) == True
    assert valideaza_datile("2025-11-01", "2025-10-28", True) == False

def test_valideaza_pret():
    assert valideaza_pret(100, True) == True
    assert valideaza_pret(0.01, True) == True
    assert valideaza_pret(-10, True) == False
    assert valideaza_pret("100", True) == False

def test_valideaza_date():
    assert valideaza_date(1, "Paris", "2025-10-01", "2025-10-28", 200.0, True) == True
    assert valideaza_date(-1, "Paris", "2025-10-01", "2025-10-28", 200.0, True) == False
    assert valideaza_date(1, "", "2025-10-01", "2025-10-28", 200.0, True) == False
    assert valideaza_date(1, "Paris", "2025-10-50", "2025-10-28", 200.0, True) == False
    assert valideaza_date(1, "Paris", "2025-11-01", "2025-10-28", 200.0, True) == False
    assert valideaza_date(1, "Paris", "2025-10-01", "2025-10-28", -10, True) == False

def test_pachet():
    """
    functie care testeaza pachet.py
    input:
        ---
    output:
        ---
    returun:
        ---
    """
    
    pachet = creaza_pachet(1, "Roma", "2025-06-10", "2025-06-20", 1000.0)

    data_inceput = datetime.strptime("2025-06-10", "%Y-%m-%d").date()
    data_sfarsit = datetime.strptime("2025-06-20", "%Y-%m-%d").date()

    assert get_id(pachet) == 1
    assert get_destinatia(pachet) == "Roma"
    assert get_data_inceput(pachet) == data_inceput
    assert get_data_sfarsit(pachet) == data_sfarsit
    assert get_pret(pachet) == 1000.0

    set_id(pachet, 2)
    assert get_id(pachet) == 2

    set_destinatia(pachet, "Paris")
    assert get_destinatia(pachet) == "Paris"

    data_inceput_nou = "2025-06-12" 
    set_data_inceput(pachet, data_inceput_nou)
    data_inceput_nou = datetime.strptime("2025-06-12", "%Y-%m-%d").date()
    assert get_data_inceput(pachet) == data_inceput_nou

    data_sfarsit_nou = "2025-07-15"
    set_data_sfarsit(pachet, data_sfarsit_nou)
    data_sfarsit_nou = datetime.strptime("2025-07-15", "%Y-%m-%d").date()
    assert get_data_sfarsit(pachet) == data_sfarsit_nou

    set_pret(pachet, 1500.0)
    assert get_pret(pachet) == 1500.0

    assert valideaza_date(0, "Atena", "2025-07-18", "2025-08-03", "sdd", test=True) == False

    assert valideaza_date(3, "sdfsd", "18/07/2025", "03/08/2025", 100, test=True) == False
    assert valideaza_date(4, "sdfdsf", "2025-02-30", "2025-03-05", 100, test=True) == False
    assert valideaza_date(5, "sddf", "", "2025-03-05", 100, test=True) == False
    assert valideaza_date(6, "dsfdf", "2025-08-10", "2025-08-01", 100, test=True) == False
    assert valideaza_date(7, "dsfsdf", "2025-07-01", "2025-07-05", -10, test=True) == False
    assert valideaza_date(8, "fddsf", "2025-07-01", "2025-07-05", "not-a-number", test=True) == False
    assert valideaza_date(-1, "sfdsdsdf", "2025-07-01", "2025-07-05", 10, test=True) == False
    assert valideaza_date(9, "", "2025-07-01", "2025-07-05", 10, test=True) == False
