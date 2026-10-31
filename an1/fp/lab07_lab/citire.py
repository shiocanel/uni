from validare import *

def citeste_id():
    """
    functie care citeste un id (int)
    input:
        - id (string)
    output:
        ---
    return:
        - id (int)
    """

    while True:
        id = input("Id: ")
        try:
            id_int = int(id)
        except ValueError:
            print("\n\n<<ERROR>> Id-ul trebuie sa fie un int pozitiv\n\n")
            continue

        if valideaza_id(id_int, True) == False:
            print("\n\n<<ERROR>> Id-ul trebuie sa fie pozitiv\n\n")
            continue    
        
        return id_int

def citeste_destinatia():
    """
    functie care citeste o destinatia nenula
    input:
        - destinatia (string)
    output:
        ---
    return:
        - destinatia (string)
    """

    destinatia = input("Destinatia: ")
    while valideaza_destinatia(destinatia, True) == False:
        print("\n\n<<ERROR>> Destinatia nu poate fi nula\n\n")
        destinatia = input("Destinatia: ")
    
    return destinatia

def citeste_data_inceput():
    """
    functie care citeste data_inceput (YYYY-MM-DD) (string)
    input:
        - data_inceput (string)
    output:
        ---
    return:
        - data_inceput (string)
    """

    data_inceput = input("Data inceput: ")
    while valideaza_data_inceput(data_inceput, True) == False:
        print("\n\n<<ERROR>> Data inceput trebuie formatata (YYYY-MM-DD)\n\n")
        data_inceput = input("Data inceput: ")
    
    return data_inceput

def citeste_data_sfarsit():
    """
    functie care citeste data_sfarsit (YYYY-MM-DD) (string)
    input:
        - data_sfarsit (string)
    output:
        ---
    return:
        - data_sfarsit (string)
    """
    
    data_sfarsit = input("Data sfarsit: ")
    while valideaza_data_sfarsit(data_sfarsit, True) == False:
        print("\n\n<<ERROR>> Data sfarsit trebuie formatata (YYYY-MM-DD)\n\n")
        data_sfarsit = input("Data sfarsit: ")

    return data_sfarsit

def citeste_pret():
    """
    functie care citeste pret (int / float)
    input:
        - pret (string)
    output:
        ---
    return:
        - pret (int / float)
    """

    while True:
        pret = input("Pret: ")
        try:
            pret_fl = float(pret)
        except ValueError:
            print("\n\n<<ERROR>> Pretul trbuie sa fie un float sau int poztiv\n\n")
            continue

        if valideaza_pret(pret_fl, True) == False:
            print("\n\n<<ERROR>> Pretul trbuie sa fie un float sau int poztiv\n\n")
            continue
        
        return pret_fl

def citeste_luna():
    """
    functie care citeste o luna (int)
    input:
        - luna (string)
    output:
        ---
    return:
        - luna (int)
    """

    while True:
        luna = input("Luna: ")
        try:
            luna_int = int(luna)
        except ValueError:
            print("\n\n<<ERROR>> Luna trbuie sa fie un int poztiv\n\n")
            continue

        if luna_int < 0:
            print("\n\n<<ERROR>> Luna trbuie sa fie un int poztiv intre 1-12\n\n")
            continue
        
        return luna_int

def citeste_numar_zile():
    """
    functie care citeste nr numarul de zile (int)
    input:
        - nr (string)
    output:
        ---
    return:
        - nr (int)
    """
    
    while True:
        nr = input("Numar de zile: ")
        try:
            nr_int = int(nr)
        except ValueError:
            print("\n\n<<ERROR>> Numarul trbuie sa fie un int poztiv\n\n")
            continue

        if nr_int < 0:
            print("\n\n<<ERROR>> Numarul trbuie sa fie un int poztiv\n\n")
            continue
        
        return nr_int