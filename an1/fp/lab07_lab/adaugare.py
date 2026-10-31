from pachet import *
from citire import *

def adauga_pachet(pachete, undo_list, do_list):
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


    destinatia = do_list[0]

    data_inceput = do_list[1]
    data_sfarsit = do_list[2]
    
    pret = float(do_list[3])

    do_list = do_list[4 : ]

    undo_list.append(pachete.copy())
    pachete.append(creaza_pachet(id, destinatia, data_inceput, data_sfarsit, pret))

    print("\n=== Pachet adaugat cu succes ===")

def modifica_pachet(pachete, undo_list, do_list):
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

    id = int(do_list[0])
    
    destinatia = do_list[1]

    data_inceput = do_list[2]
    data_sfarsit = do_list[3]
    
    pret = float(do_list[4])

    do_list = do_list[5 : ]

    undo_list.append(pachete.copy())
    pachete[id] = creaza_pachet(id, destinatia, data_inceput, data_sfarsit, pret)
    
    print("\n=== Pachet modificat cu succes ===")

echiv = {
    "1" : adauga_pachet,
    "2" : modifica_pachet
}

def adaugare(pachete, undo_list, do_list):
    """
    un ui pentru punctul de Adaugare
    input:
        - optiune (string) 
    ouput:
        ---
    return:
        ---
    """

    executa = do_list[0]
    do_list.pop(0)

    echiv[executa](pachete, undo_list, do_list)


    # while True:
    #     print("\n=== Adaugare ===")
    #     print("1. Adauga pachet de calatorie")
    #     print("2. Modifica pachet de calatorie")
    #     print("0. Iesire")
    #     optiune = input("Alege optiunea: ")
        
    #     if optiune == "1":
    #         adauga_pachet(pachete, undo_list)
    #     elif optiune == "2":
    #         modifica_pachet(pachete, undo_list)
    #     elif optiune == "0":
    #         break
    #     else:
    #         print("Optiune invalida!")