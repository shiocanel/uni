"""
enuntul problemei 11:
Se dau două numere naturale m şi n. Generaţi liste formate din numere de la 1 la n cu
proprietatea că diferenţa (în valoare absolută) între două numere consecutive din listă este
m. Tipăriţi un mesaj dacă problema nu are soluţie.
"""

def prob11_rec(n, m):
    """
    functie care rezolva recursiv problema 11

    :param n: dimensiunea sirului
    :param m: diferenta intre doua elemente consecutive 
    """
    
    ans = []
    f = [False] * (n + 1)

    def back():
        """
        functie care genereaza toate permutarile de n
        si verifica daca elementele sirului respecta proprietatea din problema
        """

        if len(ans) == n:
            print(ans)
            return True

        ok = False
        for x in range(1, n + 1):
            if not f[x]:
                if not ans or abs(ans[-1] - x) == m:
                    ans.append(x)
                    f[x] = True

                    ok = back() or ok

                    f[x] = False
                    ans.pop()

        return ok

    if not back():
        print("Nu exista solutie!!!!")


def prob11_iter(n, m):
    """
    functie care rezolva recursiv problema 11
    generem valori pentru fiecare index si verificam daca sirul satiface proprietatea

    :param n: dimensiunea sirului
    :param m: diferenta intre doua elemente consecutive 
    """
    
    ans = [0] * n
    f = [False] * (n + 1)
    k = 0
    ok = False

    while k >= 0:
        ans[k] += 1

        while ans[k] <= n and (f[ans[k]] or (k > 0 and abs(ans[k] - ans[k - 1]) != m)):
            ans[k] += 1

        if ans[k] <= n:
            f[ans[k]] = True

            if k == n - 1:
                print(ans)
                ok = True
                f[ans[k]] = False
            else:
                k += 1
                ans[k] = 0
        else:
            ans[k] = 0
            k -= 1
            if k >= 0:
                f[ans[k]] = False

    if not ok:
        print("Nu exista solutie!!!!")


prob11_rec(5, 1)

prob11_iter(5, 2)