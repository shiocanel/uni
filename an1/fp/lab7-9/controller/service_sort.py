class Sort:
    def __init__(self, cmp, key):
        """
        constructor de initializare a cmp si key
        input:
            - cmp (function)
            - key (function)
        output:
            ---
        return:
            ---
        """

        self.__cmp = cmp
        self.__key = key
    
    def quick_sort(self, arr):
        """
        functie care implementeaza quick sort si returneaza o lista sortata
        input:
            - arr (list)
        output:
            ---
        return:
            - arr (list)
        """

        if len(arr) <= 1:
            return arr
        
        pivot = arr[0]
        left = [x for x in arr[1:] if self.__cmp(self.__key(x), self.__key(pivot))]
        right = [x for x in arr[1:] if not self.__cmp(self.__key(x), self.__key(pivot))]
        
        return self.quick_sort(left) + [pivot] + self.quick_sort(right)

    def gnome_sort(self, arr):
        """
        functie care implementeaza gnome sort si returneaza o lista sortata
        input:
            - arr (list)
        output:
            ---
        return:
            - arr (list)
        """

        n = len(arr)
        ind = 0
        while ind < n:
            if ind == 0:
                ind += 1
            if not self.__cmp(self.__key(arr[ind]), self.__key(arr[ind - 1])):
                ind += 1
            else:
                arr[ind], arr[ind - 1] = arr[ind - 1], arr[ind]
                ind -= 1
        return arr