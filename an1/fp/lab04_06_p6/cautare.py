from ui import afiseaza_pachet
from pachet import *
from citire import *

def afisare_intre_dati(pachete, undo_list):
    """
    o functie care afiseaza pachetele care se regasesc in intervalul:
    [data_inceput, data_sfarsit], citite de la tastatura
    input:
        - data_inceput (YYYY-MM-DD) (string)
        - data_sfarsit (YYYY-MM-DD) (string)
    output:
        - pachetele (dictionaries)
    return:
        ---
    """

    print("\n=== Afisarea pachetelor intre un data inceput si data sfarsit ===")

    data_inceput = citeste_data_inceput()
    data_sfarsit = citeste_data_sfarsit()
    while valideaza_datile(data_inceput, data_sfarsit, True) == False:
        print("\n\n<<ERROR>> Data inceput nu poate fi dupa Data sfarsit\n\n")
        data_inceput = citeste_data_inceput()
        data_sfarsit = citeste_data_sfarsit()

    data_inceput = datetime.strptime(data_inceput, "%Y-%m-%d").date()
    data_sfarsit = datetime.strptime(data_sfarsit, "%Y-%m-%d").date()

    for pachet in pachete:
        if pachet["data_inceput"] >= data_inceput and pachet["data_sfarsit"] <= data_sfarsit:
            afiseaza_pachet(pachet)

    print("\n=== Afisarea a fost efectuata cu succes ===")    

def afisare_destinatie_mai_mic_decat_un_pret(pachete, undo_list):
    """
    o functie care afiseaza pachetele care au o destinatie si un pret mai mic decat x
    input:
        - destinatie (string)
        - x (float)
    output:
        - pachetele (dictionaries)
    return:
        ---
    """

    print("\n=== Afisarea pachetelor cu o destinatie data si cu pret < decat una data ===")

    destinatia = citeste_destinatia()

    x = citeste_pret()

    for pachet in pachete:
        if pachet["destinatia"] == destinatia and pachet["pret"] < x:
            afiseaza_pachet(pachet)

    print("\n=== Afisarea a fost efectuata cu succes ===")    

def afisare_pachet_cu_anumita_data_sfarsit(pachete, undo_list):
    """
    afiseaza pachetele care au o data de sfarsit citita de la tastatura
    input:
        - data_sfarsit (YYYY-MM-DD) (string)
    output:
        - pachetele (dictionaries)
    return:
        ---
    """

    print("\n=== Afisarea pachetelor cu o data de sfarsit ===")

    data_sfarsit = citeste_data_sfarsit()

    data_sfarsit = datetime.strptime(data_sfarsit, "%Y-%m-%d").date()

    for pachet in pachete:
        if pachet["data_sfarsit"] == data_sfarsit:
            afiseaza_pachet(pachet)

    print("\n=== Afisarea a fost efectuata cu succes ===")    

def cautare(pachete, undo_list):
    """
    o functie de ui pentru exercitiile de la Cautare
    input:
        - optiune (string)
    output:
        ---
    return:
        ---
    """

    while True:
        print("\n=== CAUTARE ===")
        print("1. Afisarea pachetelor intre 2 dati")
        print("2. Afisarea pachetelor cu o destinatie si cu pret < x")
        print("3. Afisarea pachetelor cu o anumita data de sfarsit")
        print("0. Iesire")
        optiune = input("Alege optiunea: ")
        
        if optiune == "1":
            afisare_intre_dati(pachete, undo_list)
        elif optiune == "2":
            afisare_destinatie_mai_mic_decat_un_pret(pachete, undo_list)
        elif optiune == "3":
            afisare_pachet_cu_anumita_data_sfarsit(pachete, undo_list)
        elif optiune == "0":
            print("La revedere!")
            break
        else:
            print("Optiune invalida!")
