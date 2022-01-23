from decimal import *

getcontext().prec = 75

n = int(input())

table = {1: Decimal(0.0)}

def not_drunk(x):
    if x == 1 or table.get(x) != None:
        return table[x]
    result = Decimal(1.0)
    for i in range(1, x):
        result += not_drunk(i)
    table[x] = result / Decimal(x)
    return table[x]

def drunk(x):
    result = Decimal(1.0)
    for i in range(2, x):
        result += not_drunk(i)
    return result / Decimal(x-1)

print(drunk(n))
