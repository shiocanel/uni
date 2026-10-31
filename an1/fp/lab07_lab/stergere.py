from pachet import *
from citire import *

def stergere_pachete_destinatie(pachete, undo_list, do_list):
    """
    functie pentru stergerea pachetelor care au o destinatie citita
    input:
        - destinatia (string)
    output:
        - === Stergerea a fost efectuata cu succes ===
    return:
        ---
    """

    print("\n=== Stergerea pachetelor pentru o destinatie data ===")

    destinatia = do_list[0]
    do_list.pop(0)
    
    pachete_aux = [pachet for pachet in pachete if pachet["destinatia"] != destinatia]
   
    undo_list.append(pachete.copy())
    pachete.clear()
    pachete.extend(pachete_aux)

    print("\n=== Stergerea a fost efectuata cu succes ===")    


def stergere_pachete_cu_durata(pachete, undo_list, do_list):
    """
    o functie care sterge pachete care au o durata de zile mai mici decat x zile
    input:
        - x (int)
    ouput:
        - === Stergerea a fost efectuata cu succes ===
    return:
        ---
    """

    print("\n=== Stergerea pachetelor cu o durata de zile mai mici decat x zile ===")

    x = int(do_list[0])
    do_list.pop(0)

    pachete_aux = [pachet for pachet in pachete if (pachet["data_sfarsit"] - pachet["data_inceput"]).days <= x]
    
    undo_list.append(pachete.copy())
    pachete.clear()
    pachete.extend(pachete_aux)

    print("\n=== Stergerea a fost efectuata cu succes ===")    

def stergere_pachet_cu_pret_mai_mare(pachete, undo_list, do_list):
    """
    o functie care sterge pachetele care au un pret mai mare decat un x citit de la tastatura
    input:
        - x (float)
    output:
        - === Stergerea a fost efectuata cu succes ===
    return:
        ---
    """

    print("\n=== Stergerea pachetelor cu un pret mai mare decat x ===")

    x = float(do_list[0])
    do_list.pop(0)

    pachete_aux = [pachet for pachet in pachete if pachet["pret"] <= x]
    
    undo_list.append(pachete.copy())
    pachete.clear()
    pachete.extend(pachete_aux)

    print("\n=== Stergerea a fost efectuata cu succes ===") 

echiv = {
    "1" : stergere_pachete_destinatie,
    "2" : stergere_pachete_cu_durata,
    "3" : stergere_pachet_cu_pret_mai_mare
}  

def stergere(pachete, undo_list, do_list):
    """
    o functie ui pentru rezolvarea punctelor de la Stergere
    input:
        - optiune (string)
    output:
        ---
    return:
        ---
    """

    executa = do_list[0]
    do_list.pop(0)

    echiv[executa](pachete, undo_list, do_list)


    # while True:
    #     print("\n=== STERGERE ===")
    #     print("1. Stergerea pachetelor pentru o destinatie data")
    #     print("2. Stergerea tuturor pachetelor cu o durata mai scurta decat x zile")
    #     print("3. Stergerea tuturor pachetelor cu o pretul mai mare decat o suma")
    #     print("0. Iesire")
    #     optiune = input("Alege optiunea: ")
        
    #     if optiune == "1":
    #         stergere_pachete_destinatie(pachete, undo_list)
    #     elif optiune == "2":
    #         stergere_pachete_cu_durata(pachete, undo_list)
    #     elif optiune == "3":
    #         stergere_pachet_cu_pret_mai_mare(pachete, undo_list)
    #     elif optiune == "0":
    #         print("La revedere!")
    #         break
    #     else:
    #         print("Optiune invalida!")

