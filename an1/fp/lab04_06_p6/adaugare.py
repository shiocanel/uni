from pachet import *
from citire import *

def adauga_pachet(pachete, undo_list):
    """
    adauga pachetul in lista pachete
    input:
        - id (int)
        - destinatia (string)
        - data_inceput (datetime)
        - data_sfarsit (datetime)
        - pret (float)
    output:
        - === Pachet adaugat cu succes === (daca se adauga cu succes)
    return:
        ---
    """

    print("\n=== Adauga pachetul ===")
    id = len(pachete)


    destinatia = citeste_destinatia()

    data_inceput = citeste_data_inceput()
    data_sfarsit = citeste_data_sfarsit()
    while valideaza_datile(data_inceput, data_sfarsit, True) == False:
        print("\n\n<<ERROR>> Data inceput nu poate fi dupa Data sfarsit\n\n")
        data_inceput = citeste_data_inceput()
        data_sfarsit = citeste_data_sfarsit()
    
    pret = citeste_pret()

    undo_list.append(pachete.copy())
    pachete.append(creaza_pachet(id, destinatia, data_inceput, data_sfarsit, pret))

    print("\n=== Pachet adaugat cu succes ===")

def modifica_pachet(pachete, undo_list):
    """
    modifica pachetul dupa index
    input:
        - id (int)
        - destinatia (string)
        - data_inceput (string)
        - data_sfarsit (string)
        - pret (int)
    output:
        ---
    return:
        ---
    """

    print("\n=== Modifica pachetul ===")

    id = citeste_id()
    while id >= len(pachete):
        print(f"id-ul trebuie sa fie < {len(pachete)}")
        id = citeste_id()
    
    destinatia = citeste_destinatia()

    data_inceput = citeste_data_inceput()
    data_sfarsit = citeste_data_sfarsit()
    while valideaza_datile(data_inceput, data_sfarsit, True) == False:
        print("\n\n<<ERROR>> Data inceput nu poate fi dupa Data sfarsit\n\n")
        data_inceput = citeste_data_inceput()
        data_sfarsit = citeste_data_sfarsit()
    
    pret = citeste_pret()

    undo_list.append(pachete.copy())
    pachete[id] = creaza_pachet(id, destinatia, data_inceput, data_sfarsit, pret)
    
    print("\n=== Pachet modificat cu succes ===")

def adaugare(pachete, undo_list):
    """
    un ui pentru punctul de Adaugare
    input:
        - optiune (string) 
    ouput:
        ---
    return:
        ---
    """

    while True:
        print("\n=== Adaugare ===")
        print("1. Adauga pachet de calatorie")
        print("2. Modifica pachet de calatorie")
        print("0. Iesire")
        optiune = input("Alege optiunea: ")
        
        if optiune == "1":
            adauga_pachet(pachete, undo_list)
        elif optiune == "2":
            modifica_pachet(pachete, undo_list)
        elif optiune == "0":
            break
        else:
            print("Optiune invalida!")