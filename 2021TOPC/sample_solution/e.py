def s5(n):
    return n*n*(n+1)*(n+1)*(2*n*n+2*n-1) // 12

def balance(n, p, q, x):
    return q*s5(n) - p*n + x

p, q = [int(_) for _ in input().split()]

# finding x: won't be too long
x = 0
for i in range(1,10**99):
    x += p
    if p <= q * i**5:
        break
    x -= q * i**5

print(x)

lower = 0
upper = 10**99
while lower != upper - 1:
    mid = (lower + upper) // 2
    if balance(mid, p, q, x) < 10**99:
        lower = mid
    else:
        upper = mid

print(upper)
