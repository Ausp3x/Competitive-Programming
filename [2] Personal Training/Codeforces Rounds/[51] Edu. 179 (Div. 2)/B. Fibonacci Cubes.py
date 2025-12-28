from math import *

F = [1, 1, 2]
for i in range(3, 12):
    F.append(F[-2] + F[-1])

def solve():
    n, m = map(int, input().split())
    
    ans = ''
    for _ in range(m):
        A = list(map(int, input().split()))
        A.sort()
        
        if A[0] >= F[n] and A[1] >= F[n] and A[2] >= F[n + 1]:
            ans += '1'
        else:
            ans += '0'

    print(ans)

    return

t = int(input())
for _ in range(t):
    solve()