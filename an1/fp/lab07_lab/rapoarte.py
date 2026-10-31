from pachet import *
from ui import afiseaza_pachet
from citire import *

def afisare_numar_pachete_destinatie(pachete, undo_list, do_list):
    """
    o functie care afiseaza numarul de pachete care au o destinatie citita
    input:
        - destinatia (string)
    output:
        - cnt (int)
    return:
        ---
    """

    print("\n=== Afisarea numarului pachetelor pentru o destinatie data ===")
    destinatia = do_list[0]

    do_list = do_list[1 : ]

    cnt = 0
    for pachet in pachete:
        if pachet["destinatia"] == destinatia:
            cnt += 1

    print(f"Numarul de oferte pentru destinatia {destinatia} este: {cnt}")

    print("\n=== Tiparirea a fost efectuata cu succes ===")    

def afisare_pachete_crescator(pachete, undo_list, do_list):
    """
    o functie care afiseaza pachetele disponibile in ordine crescatoare din intervalul
    [data_inceput, data_sfarsit]
    input:
        - data_inceput (YYYY-MM-DD) (string)
        - data_sfarsit (YYYY-MM-DD) (string)
    ouput:
        - pachetele sortate (dictionaries)
    return:
        ---
    """
    
    print("\n=== Afisarea pachetelor disponibile in ordine crescatoare dntr-o anumita perioada ===")

    data_inceput = do_list[0]
    data_sfarsit = do_list[1]
    do_list = do_list[2 : ]

    data_inceput = datetime.strptime(data_inceput, "%Y-%m-%d").date()
    data_sfarsit = datetime.strptime(data_sfarsit, "%Y-%m-%d").date()

    pachete_aux = [pachet for pachet in pachete if (data_inceput <= pachet["data_inceput"] and data_sfarsit >= pachet["data_sfarsit"])]
    pachete_aux.sort(key = lambda pachet: pachet["pret"])
    
    for pachet in pachete_aux:
        afiseaza_pachet(pachet, undo_list, do_list)

    print("\n=== Tiparirea a fost efectuata cu succes ===")    


def afisare_medie_destinatie(pachete, undo_list, do_list):
    """
    functie care afiseaza media pachetelor pentru o destinatie citita
    input:
        - destinatia (string)
    output:
        - media (float)
    return:
        ---
    """

    print("\n=== Afisarea mediei pachetelor disponibile pentru o anumita destinatie ===")

    destinatia = do_list[0]
    do_list = do_list[1 : ]

    sum = 0
    cnt = 0

    for pachet in pachete:
        if pachet["destinatia"] == destinatia:
            sum += pachet["pret"]
            cnt += 1

    if cnt == 0:
        print("Nu avem astfel de destinatii :(")
        return
    
    print(f"Media preturilor pentru destinatia {destinatia}: {sum / cnt}")

echiv = {
    "1" : afisare_numar_pachete_destinatie,
    "2" : afisare_pachete_crescator,
    "3" : afisare_medie_destinatie
}  

def rapoarte(pachete, undo_list, do_list):
    """
    o functie ui pentru punctele de la Rapoarte
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
    #     print("\n=== RAPOARTE ===")
    #     print("1. Afisarea numarul de pachete pentru o destinatie data")
    #     print("2. Afisarea pachetelor in ordine crescatoare a pretului dupa data")
    #     print("3. Afisarea mediei de pret pentru o destinatie")
    #     print("0. Iesire")
    #     optiune = input("Alege optiunea: ")
        
    #     if optiune == "1":
    #         afisare_numar_pachete_destinatie(pachete, undo_list)
    #     elif optiune == "2":
    #         afisare_pachete_crescator(pachete, undo_list)
    #     elif optiune == "3":
    #         afisare_medie_destinatie(pachete, undo_list)
    #     elif optiune == "0":
    #         print("La revedere!")
    #         break
    #     else:
    #         print("Optiune invalida!")
