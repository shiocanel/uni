def undo(pachete, undo_list, test = False):
    """
    functie care face undo la ultima modificare a pachete (dictionaries)
    input:
        ---
    output:
        ---
    return:
        ---
    """

    if len(undo_list) == 0:
        if test == False:
            print("Nu avem nimic de undo-it")

        return False
    
    pachete.clear()
    aux = undo_list[-1]
    undo_list.pop()

    pachete.extend(aux)

    if test == False:
        print("\n<<Am dat undo pentru tu>>\n")

    return True