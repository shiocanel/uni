from pachet import *

def afisare(pachete):
    """
    un ui pentru afisarea pachetelor
    input:
        ---
    output:
        de facut
    return:
        ---
    """

    for pachet in pachete:
        print(f"\nId: {pachet["id"]} \nDestinatia: {pachet["destinatia"]} \nData inceput: {pachet["data_inceput"]} \nData sfarsit: {pachet["data_sfarsit"]} \nPret: {pachet["pret"]}\n")

def afiseaza_pachet(pachet):
    """
    functie care afiseaza un pachet
    input:
        - pachet (dictionaries)
    output:
        de facut
    return:
        ---
    """

    print(f"\nId: {pachet["id"]} \nDestinatia: {pachet["destinatia"]} \nData inceput: {pachet["data_inceput"]} \nData sfarsit: {pachet["data_sfarsit"]} \nPret: {pachet["pret"]}\n")


def init_params(pachete, undo_list):
    """
    o functie auxiliare pentru a initializa lista de pachete cu informatii
    input:
        ---
    output:
        ---
    return:
        ---
    """

    pachete.append(creaza_pachet(0, "Atena", "2025-07-18", "2025-08-03", 302))
    
    undo_list.append(pachete.copy())
    pachete.append(creaza_pachet(1, "Barcelona", "2025-08-22", "2025-08-30", 124))
    undo_list.append(pachete.copy())
    pachete.append(creaza_pachet(2, "Barcelona", "2025-06-02", "2025-06-30", 3411))
    undo_list.append(pachete.copy())
    pachete.append(creaza_pachet(3, "Barcelona", "2025-06-12", "2025-06-27", 1222))
    undo_list.append(pachete.copy())
    pachete.append(creaza_pachet(4, "Roma", "2025-06-11", "2025-09-30", 3011))
    undo_list.append(pachete.copy())
    pachete.append(creaza_pachet(5, "Roma", "2025-09-10", "2025-11-22", 3921))

from adaugare import adaugare
from stergere import stergere
from cautare import cautare
from rapoarte import rapoarte
from filtrare import filtrare
from undo import undo

def menu(pachete, undo_list):
    """
    un ui de menu
    input:
        - optiune (string)
    ouput:
        ---
    return:
        ---
    """

    init_params(pachete, undo_list)

    while True:
        print("\n=== MENIU ===")
        print("1. Adaugare")
        print("2. Stergere")
        print("3. Cautare")
        print("4. Rapoarte")
        print("5. Filtrare")
        print("6. Undo")
        print("#. Afisare")        
        print("0. Iesire")
        optiune = input("Alege optiunea: ")
        
        if optiune == "1":
            adaugare(pachete, undo_list)
        elif optiune == "2":
            stergere(pachete, undo_list)
        elif optiune == "3":    
            cautare(pachete, undo_list)
        elif optiune == "4":
            rapoarte(pachete, undo_list)
        elif optiune == "5":
            filtrare(pachete, undo_list)
        elif optiune == "6":
            undo(pachete, undo_list)
        elif optiune == "#":
            afisare(pachete)
        elif optiune == "0":
            print("La revedere!")
            break
        else:
            print("Optiune invalida!")

