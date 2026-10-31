def isBisect(x):
    """
    daca un an este bisect sau nu
    input:
        - an (int)
    output:
        True daca e bisect
        Fals in caz contrar
    """
    
    if x % 400 == 0:
        return True
    
    if x % 100 == 0:
        return False
    
    if x % 4 == 0:
        return True
    
    return False

def citeste():
    an1 = int(input("An: "))
    x = int(input("Zi: "))
    return an1, x


def dataCalendaristica(an1 = None, x = None):
    if(an1 is None):
        an1, x = citeste()

    # luna1 = int(input("Luna: ")) - 1
    # zi1 = int(input("Zi: "))

    lunile = [31, 28 + (isBisect(an1)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    luna_idx = 0

    # ans = 0
    # while luna_idx < luna1:
    #     ans += lunile[luna_idx]
    #     luna_idx += 1

    # ans += zi1

    # print(f"Numarul de zile: {ans}")

    while x > lunile[luna_idx]:
        x -= lunile[luna_idx]
        luna_idx += 1

    ans = f"Data: {x}/{luna_idx + 1}/{an1}"
    print(ans)

    return ans

def meniu():
    test_program()
    
    while True:
        print("\n=== MENIU ===")
        print("1. Data calendaristica dupa numarul de ordine al zilei")
        print("0. Ieșire")
        optiune = input("Alege opțiunea: ")
        
        if optiune == "1":
            dataCalendaristica()
        elif optiune == "0":
            print("La revedere!")
            break
        else:
            print("Opțiune invalidă!")

def test_program():
    test_DataCalendaristica()
    test_isBisect()

def test_DataCalendaristica():
    assert (dataCalendaristica(2024, 60) == "Data: 29/2/2024")
    assert (dataCalendaristica(2023, 59) == "Data: 28/2/2023")
    assert (dataCalendaristica(2023, 365) == "Data: 31/12/2023")

def test_isBisect():
    assert(isBisect(2000) == True)
    assert(isBisect(2004) == True)
    assert(isBisect(2008) == True)
    assert(isBisect(2012) == True)
    assert(isBisect(2016) == True)
    
    assert(isBisect(2001) == False)
    assert(isBisect(2002) == False)
    assert(isBisect(2003) == False)
    assert(isBisect(2005) == False)
    assert(isBisect(2023) == False)
    

if __name__ == "__main__":
    meniu()
