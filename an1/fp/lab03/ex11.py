def menu():
    print("1) Citeste lista")
    print("2) Secventa de lungime maxima care are suma maxima")
    print("3) Secventa de lungime maxima care are oricare 2 elemente consecutive sunt de semne contrare")
    print("4) Secventa de lungime maxima care are oricare 2 elemente consecutive sunt de semne contrare")
    print("0) Exit")

def citeste(a):
    """
    citeste lista de numere
    input: 
            a - list, lista cu numere
    output:
            nimic
    """


    n = int(input("n: "))

    for i in range(n):
        x = int(input())
        a.append(x)

def find_secventa(a, l, r):
    """
    gaseste secventa de la l..r
    input:
            a - list, lista cu numere
            l - int, indexul de stanga
            r - int, indexul de dreapta
    """


    ans = []
    for i in range(l, r + 1):
        ans.append(a[i])
    
    return ans

def afiseaza_res(res):
    for i in res:
        print(i, end=' ')
    print()

def ex11(a):
    ans = a[0]
    mx = a[0]
    
    idx = 0
    n = len(a)

    for i in range(1, n):
        mx = max(a[i], a[i] + mx)
        if mx >= ans:
            ans = mx
            idx = i

    print(f"Secventa maxima cu proprietatea 11: {ans}")

    sum = 0
    res = []
    l = idx
    r = idx
    while idx >= 0 and sum != ans:
        res.append(a[idx])
        sum += a[idx]
        idx -= 1
    
    l = idx + 1

    res = find_secventa(a, l, r)
    afiseaza_res(res)

def ex12(a):
    ans = 0
    n = len(a)

    cnt = 1
    l = 0
    r = 0
    for i in range(1, n):
        if a[i] * a[i - 1] < 0:
            cnt += 1
        else:
            ans = max(ans, cnt)
            r = i - 1
            cnt = 1
    
    if cnt > ans:
        ans = cnt
        r = n - 1

    l = r - ans + 1
    print(f"Lungimea maxima cu proprietatea 12: {ans}")

    res = find_secventa(a, l, r)
    afiseaza_res(res)

def ex10(a):
    ans = 0
    n = len(a)

    cnt = 1
    l = 0
    r = 0
    for i in range(1, n - 2):
        if ((a[i + 1] - a[i]) * (a[i + 2] - a[i + 1])) < 0:
            cnt += 1
        else:
            ans = max(ans, cnt)
            r = i - 1
            cnt = 1

    if cnt > ans:
        ans = cnt
        r = i - 1

    l = r - ans + 1

    print(f"Lungimea maxima cu proprietatea 10: {ans}")

    res = find_secventa(a, l, r)
    afiseaza_res(res)


def run():
    a = []
    while True:
        menu()

        opt = int(input("Optiune: "))

        print()
        if opt == 1:
            citeste(a)
        elif opt == 2:
            ex11(a)
        elif opt == 3:
            ex12(a)
        elif opt == 4:
            ex10(a)
        else:
            break
        
        print()

run()