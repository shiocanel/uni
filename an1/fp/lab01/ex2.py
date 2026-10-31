import math

def prim(n):
    if(n < 2):
        return False
    if(n == 2):
        return True
    if(n % 2 == 0):
        return False
    
    for i in range(3, int(math.sqrt(n)) + 1):
        if(n % i == 0):
            return False
    
    return True

n = int(input("Verifica daca prim: "))

print("prim" if prim(n) == True else "nu tocmai prim")

        