n = int(input("numar1: "))
m = int(input("numar2: "))

while(m != 0):
    r = n % m
    n = m
    m = r

print(f"gcd: {n}")



# a * b = lcm(a, b) * gcd(a, b)