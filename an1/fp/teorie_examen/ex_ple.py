a = [1, 2, 3, 4, 5]

a = list(filter(lambda x : x <= 3, a[ : ]))

print(a)













# def divide(a, left = 0, right = None):
#     if right is None:
#         right = len(a) - 1

#     if right - left < 1:
#         if left % 2 == 0:
#             return a[left]
#         else:
#             return 1

#     if right - left == 1:
#         if left % 2 == 0:
#             return a[left]
#         else:
#             return a[right]

#     mid = (left + right) // 2

#     return divide(a, left, mid) * divide(a, mid + 1, right)


# a = [1, 2, 3, 4, 10, 2, 2]

# print(divide(a))

























# def binary_search_it(a, x):
#     l = -1
#     r = len(a)


#     while l < r - 1:
#         mid = (l + r) // 2

#         if a[l] == x:
#             return l
#         if a[l] < x:
#             l = mid + 1
#         else:
#             r = mid - 1

#     return -1


# def binary_search_rec(a, x, l = -1, r = None):
#     if r is None:
#         r = len(a)

#     mid = (l + r) // 2

#     if a[mid] == x:
#         return mid
    
#     if a[mid] < x:
#         return binary_search_rec(a, mid + 1, r)
#     if a[mid] > x:
#         return binary_search_rec(a, l, mid - 1)
    
#     return -1

# # 5 4 3 2 1 0 n = 6
# # 5 9 12 14 15 15



# # 2n * (2n - 2) - (2n - 2)(2n - 1) / 2 - (2n - 2)
# # 4n^2 - 4n - 2n^2 + n + 2n - 1 - 2n + 2
# #  2n^2 - 3n + 1

# # sum = n * (n + 1) / 2


