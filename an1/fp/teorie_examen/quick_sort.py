def quick_sort(a):
    if len(a) <= 1:
        return a
    
    pivot = a[0]
    l = [x for x in a[1 : ] if x < pivot]
    r = [x for x in a[1 : ] if x >= pivot]

    return quick_sort(l) + [pivot] + quick_sort(r)

a = [10, 3, 5, 13, 5, 22, 4, 1]

a = quick_sort(a)

print(a)    


# in-palce

def get_pivot(a, left, right):
    pivot = a[left]

    i = left
    j = right
    while i < j:
        while a[j] >= pivot and i < j:
            j -= 1
        a[i] = a[j]

        while a[i] <= pivot and i < j:
            i += 1
        a[j] = a[i] 
    a[i] = pivot
    
    return i


def quick_sort(a, left = 0, right = None):
    if right is None:
        right = len(a) - 1

    pos = get_pivot(a, left, right)

    if left < pos - 1:
        quick_sort(a, left, pos - 1)
    if pos + 1 < right:
        quick_sort(a, pos + 1, right)        
