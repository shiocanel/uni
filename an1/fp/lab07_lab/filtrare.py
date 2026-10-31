from ui import afiseaza_pachet
from pachet import *
from citire import *

def elminare_pret_destinatie(pachete, undo_list, do_list):
    """
    filtreaza pachetele care au un pret < x si destinatie diferita
    input:
        - destinatia (string)
        - x (float)
    output:
        ---
    return:
        ---
    """
    
    print("\n=== Eliminarea pachetelor cu un pret < x si cu destinatie diferita de destinatie ===")

    destinatia = do_list[0]

    x = float(do_list[1])

    do_list = do_list[2 : ]

    pachete_aux = list(filter(lambda p : p["pret"] <= x and p["destinatia"] != destinatia, pachete))    # pachete_aux = filter(lambda pachet : pachet["destinatia"] != destinatia, pachete)

    undo_list.append(pachete.copy())
    pachete.clear()
    pachete.extend(pachete_aux)

    print("\n=== Eliminarea pachetelor a avut loc cu succes ===")

def eliminare_pachete_dintr_o_luna(pachete, undo_list, do_list):
    """
    filtreaza pachetele care contin zile dint-o luna citita
    input:
        - luna (int)
    output:
        ---
    return:
        ---
    """

    print("\n=== Elminarea pachetelor care contine luna citita ===")

    luna = do_list[0]
    do_list = do_list[1 : ]

    pachete_aux = list(filter(lambda p : p["data_inceput"].month > luna or p["data_sfarsit"].month < luna, pachete))

    undo_list.append(pachete.copy())
    pachete.clear()
    pachete.extend(pachete_aux)

    print("\n=== Eliminarea pachetelor a avut loc cu succes ===")


echiv = {
    "1" : elminare_pret_destinatie,
    "2" : eliminare_pachete_dintr_o_luna
}

def filtrare(pachete, undo_list, do_list):
    """
    o functie de ui pentru exercitiile de la Cautare
    input:
        - optiune (string)
    output:
        ---
    return:
        ---
    """

    executa = do_list[0]
    do_list = do_list[1 : ]

    echiv[executa](pachete, undo_list, do_list)

    # while True:
    #     print("\n=== FILTRARE ===")
    #     print("1. Eliminarea pachetelor cu un pret > x si destinatie diferit")
    #     print("2. Elminarea pachetelor care sunt dintr-o luna citita")
    #     print("0. Iesire")
    #     optiune = input("Alege optiunea: ")
        
    #     if optiune == "1":
    #         elminare_pret_destinatie(pachete, undo_list)
    #     elif optiune == "2":
    #         eliminare_pachete_dintr_o_luna(pachete, undo_list)
    #     elif optiune == "0":
    #         print("La revedere!")
    #         break
    #     else:
    #         print("Optiune invalida!")
