"""
Structura pachet : {
    'id' : int,
    'destinatia': string,
    'data_inceput':  datetime (YYYY-MM-DD),
    'data_sfarsit': datetime (YYYY-MM-DD),
    'pret': float
}
"""

from validare import *

def creaza_pachet(id, destinatia, data_inceput, data_sfarsit, pret):
    """
    creaza pachetul si il returneaza ca un dictionar
    input:
        - id (int)
        - destinatia (string)
        - data_inceput (YYYY-MM-DD) (string)
        - data_sfarsit (YYYY-MM-DD) (string)
        - pret (float)
    output:
        ---
    return:
        - pachet (id, destinatia, data_inceput, data_sfarsit, pret) (dictionaries)
    """

    valideaza_date(id, destinatia, data_inceput, data_sfarsit, pret)

    data_inceput = datetime.strptime(data_inceput, "%Y-%m-%d").date()
    data_sfarsit = datetime.strptime(data_sfarsit, "%Y-%m-%d").date()

    return {
        "id" : id,
        "destinatia" : destinatia,
        "data_inceput" : data_inceput,
        "data_sfarsit" : data_sfarsit,
        "pret" : pret
    } 

def get_id(pachet):
    """
    functie ce returneaza id-ul (int) din pachet
    input:
        - pachet (dictionaries)
    output:
        ---
    return:
        - id (int)
    """

    return pachet["id"]

def get_destinatia(pachet):
    """
    functie ce returneaza destinatia (string) din pachet
    input:
        - pachet (dictionaries)
    output:
        ---
    return:
        - destinatia (string)
    """

    return pachet["destinatia"]

def get_data_inceput(pachet):
    """
    functie ce returneaza data_inceput (datetime) din pachet
    input:
        - pachet (dictionaries)
    output:
        ---
    return:
        - data_inceput (datetime)
    """

    return pachet["data_inceput"]

def get_data_sfarsit(pachet):
    """
    functie ce returneaza data_sfarsit (datetime) din pachet
    input:
        - pachet (dictionaries)
    output:
        ---
    return:
        - data_sfarsit (datetime)
    """

    return pachet["data_sfarsit"]

def get_pret(pachet):
    """
    functie ce returneaza pret (float) din pachet
    input:
        - pachet (dictionaries)
    output:
        ---
    return:
        - pret (float)
    """

    return pachet["pret"]

def set_id(pachet, id_nou):
    """
    functie ce modifica id-ul (int) in id_nou din pachet
    input:
        - pachet (dictionaries)
        - id_nou (int)
    output:
        ---
    return:
        ---
    """

    valideaza_date(id_nou, pachet["destinatia"], pachet["data_inceput"].strftime("%Y-%m-%d"), pachet["data_sfarsit"].strftime("%Y-%m-%d"), pachet["pret"])

    pachet["id"] = id_nou

def set_destinatia(pachet, destinatia_nou):
    """
    functie ce modifica destinatia (string) in destinatia_nou din pachet
    input:
        - pachet (dictionaries)
        - destinatia_nou (string)
    output:
        ---
    return:
        ---
    """

    valideaza_date(pachet["id"], destinatia_nou, pachet["data_inceput"].strftime("%Y-%m-%d"), pachet["data_sfarsit"].strftime("%Y-%m-%d"), pachet["pret"])

    pachet["destinatia"] = destinatia_nou

def set_data_inceput(pachet, data_inceput_nou):
    """
    functie ce modifica data_inceput (datetime) in data_inceput_nou din pachet
    input:
        - pachet (dictdictionaries)
        - data_inceput_nou (YYYY-MM-DD) (string)
    output:
        ---
    return:
        ---
    """

    valideaza_date(pachet["id"], pachet["destinatia"], data_inceput_nou, pachet["data_sfarsit"].strftime("%Y-%m-%d"), pachet["pret"])
    data_inceput_nou = datetime.strptime(data_inceput_nou, "%Y-%m-%d").date()

    pachet["data_inceput"] = data_inceput_nou

def set_data_sfarsit(pachet, data_sfarsit_nou):
    """
    functie ce modifica data_sfarsit_nou (datetime) in data_sfarsit_nou din pachet
    input:
        - pachet (dictionaries)
        - data_sfarsit_nou (YYYY-MM-DD) (string)
    output:
        ---
    return:
        ---    
    """

    valideaza_date(pachet["id"], pachet["destinatia"], pachet["data_inceput"].strftime("%Y-%m-%d"), data_sfarsit_nou, pachet["pret"])
    data_sfarsit_nou = datetime.strptime(data_sfarsit_nou, "%Y-%m-%d").date()

    pachet["data_sfarsit"] = data_sfarsit_nou

def set_pret(pachet, pret_nou):
    """
    functie ce modifica pret_nou (float) din pachet
    input:
        - pachet (dictionaries)
        - pret_nou (float)
    output:
        ---
    return:
        ---    
    """

    valideaza_date(pachet["id"], pachet["destinatia"], pachet["data_inceput"].strftime("%Y-%m-%d"), pachet["data_sfarsit"].strftime("%Y-%m-%d"), pret_nou)

    pachet["pret"] = pret_nou