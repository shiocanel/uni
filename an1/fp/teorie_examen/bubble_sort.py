def bubble_sort(a):
    ok = False
    while not ok:
        ok = True
        
        for i in range(len(a) - 1):
            if a[i] > a[i + 1]:
                a[i], a[i + 1] = a[i + 1], a[i]
                ok = False

a = [10, 3, 5, 13, 5, 22, 4, 1]
bubble_sort(a)

print(a)

# algoritm de sortare in-place

"""
caz favorabil : theta(n)
caz defavorabil: theta(n^2)
caz mediu:

    n * (n + 1) / n + n * (n + 1) + ...
    n * n * (n + 1) / n = n * (n + 1) = theta(n^2)

    T(n) = O(n^2)

"""