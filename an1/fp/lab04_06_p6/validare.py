from datetime import datetime

def erori(msg, test):
    """
    functie care returneza un mesaj in cazul in care exista o eroare in validarea datelor
    input:
        - msg (string)
        - test (bool)
    output:
        - msg (in cazul in care test == False)
    return:
        - False (in cazul in care test == True)
    """

    if test:
        return False
    raise ValueError(msg)

def valideaza_id(id, test):
    """
    functie care valideaza id-ul (int)
    input:
        - id (int)
        - test (bool)
    output:
        ---
    return:
        - erori(msg, test)
    """
    
    if not isinstance(id, (int)):
        return erori("id trebuie sa fie un int", test)

    if id < 0:
        return erori("id-ul nu poate fi negativ", test)
    return True
    
def valideaza_destinatia(destinatia, test):
    """
    functie care valideaza destinatia (string)
    input:
        - destinatia (string)
        - test (bool)
    output:
        ---
    return:
        - erori(msg, test)
    """
    
    if destinatia == "":
        return erori("destinatia nu poate fi vida", test)
    return True
    
def valideaza_data_inceput(data_inceput, test):
    """
    functie care valideaza data_inceput (YYYY-MM-DD) (string)
    input:
        - data_inceput (string)
        - test (bool)
    output:
        ---
    return:
        - erori(msg, test)
    """
    
    try:
        datetime.strptime(data_inceput, "%Y-%m-%d")
    except ValueError:
        return erori("data_inceput trebuie sa fie fromatat astfel: YYYY-MM-DD", test)
    return True
    
def valideaza_data_sfarsit(data_sfarsit, test):
    """
    functie care valideaza data_sfarsit (YYYY-MM-DD) (string)
    input:
        - data_inceput (string)
        - test (bool)
    output:
        ---
    return:
        - erori(msg, test)
    """

    try:
        datetime.strptime(data_sfarsit, "%Y-%m-%d")
    except ValueError:
        return erori("data_sfarsit trebuie sa fie fromatat astfel: YYYY-MM-DD", test)
    return True
    
def valideaza_datile(data_inceput, data_sfarsit, test):
    """
    functie care valideaza ca datile sa fie in ordinea corecta
    input:
        - data_inceput (string)
        - data_sfarsit (string)
        - test (bool)
    output:
        ---
    return:
        - erori(msg, test)
    """
    
    data_inceput_aux  = datetime.strptime(data_inceput, "%Y-%m-%d").date()
    data_sfarsit_aux = datetime.strptime(data_sfarsit, "%Y-%m-%d").date()

    if data_inceput_aux > data_sfarsit_aux:
        return erori("data_inceput nu poate fi mai mare decat data_sfarsit", test)
    return True
    
def valideaza_pret(pret, test):
    """
    functie care valideaza ca pretul sa fie in de tip int sau float si ca este poziti > 0
    input:
        - pret (float)
        - test (bool)
    output:
        ---
    return:
        - erori(msg, test)
    """
    
    if not isinstance(pret, (float, int)):
        return erori("pretul trebuie sa fie float sau int", test)
    if pret <= 0:
        return erori("pretul nu poate fi negativ", test)
    return True

def valideaza_date(id, destinatia, data_inceput, data_sfarsit, pret, test = False):
    """
    valideaza datele primite atunci cand vrem sa cream un pachet
    input:
        - id (int)
        - destinatia (string)
        - data_inceput (string)
        - data_sfarsit (string)
        - pret (float)
    output:
        ---
    return:
        - True (daca datele sunt corecte)
        - Fals (daca datele nu sunt corecte)
    """

    if valideaza_id(id, test) == False:
        return False

    if valideaza_destinatia(destinatia, test) == False:
        return False

    if valideaza_data_inceput(data_inceput, test) == False:
        return False

    if valideaza_data_sfarsit(data_sfarsit, test) == False:
        return False

    if valideaza_datile(data_inceput, data_sfarsit, test) == False:
        return False

    if valideaza_pret(pret, test) == False:
        return False

    return True