def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) // 2

    left = arr[ : mid]
    right = arr[mid : ]

    left = merge_sort(left)
    right = merge_sort(right)

    return merge(left, right)

def merge(left, right):
    ans = []
    i = j = 0

    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            ans.append(left[i])
            i += 1
        else:
            ans.append(right[j])
            j += 1
        
    ans.extend(left[i : ])
    ans.extend(right[j : ])

    return ans

unsortedArr = [3, 7, 6, -10, 15, 23.5, 55, -13]
sortedArr = merge_sort(unsortedArr)
print("Sorted array:", sortedArr)


"""
Spatiu = theta(nlogn)
"""