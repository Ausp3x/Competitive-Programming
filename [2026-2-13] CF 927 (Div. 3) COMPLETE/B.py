from math import *

def solve():
    n = int(input())
    A = list(map(int, input().split()))
    
    cur = A[0]
    for i in range(1, n):
        d = (cur + A[i]) // A[i]
        cur = d * A[i]
    
    print(cur)
    
    return

t = int(input())
for _ in range(t):
    solve()