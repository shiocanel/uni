n = int(input(f"number of numbers: "))

sum = 0
for i in range(n):
    x = int(input("number: "))
    sum += x

print(f"sum: {sum}")




def functie1():
    ...
def functie2():
    ...

"""

def meniu():
    test_program()
    
    while True:
        print("\n=== MENIU ===")
        print("1. Rulează funcție1")
        print("2. Rulează funcție2")
        print("0. Ieșire")
        optiune = input("Alege opțiunea: ")
        
        if optiune == "1":
            functie1()
        elif optiune == "2":
            functie2()
        elif optiune == "0":
            print("La revedere!")
            break
        else:
            print("Opțiune invalidă!")

def test_program():
    ...

def test_functie1():
    ...

def test_functie2():
    ...

if __name__ == "__main__":
    meniu()

"""