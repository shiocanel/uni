def selection_sort(a):
    for i in range(len(a) - 1):
        min_idx = i

        for j in range(i + 1, len(a)):
            if a[j] < a[min_idx]:
                min_idx = j

        a[i], a[min_idx] = a[min_idx], a[i]


a = [10, 3, 5, 13, 5, 22, 4, 1]

selection_sort(a)

print(a)