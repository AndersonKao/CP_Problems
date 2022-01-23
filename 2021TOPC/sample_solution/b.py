N = 1000000
table = [1] * (N+1)
table[0] = table[1] = 0
for i in range(2, N+1):
    for j in range(i + i, N+1, i):
        table[j] += i

T = int(input())
for n in map(int, input().split()):
    if table[n] == n:
        print('perfect')
    elif table[n] < n:
        print('deficient')
    else:
        print('abundant')
