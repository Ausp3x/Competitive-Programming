from math import *

def solve():
    n, G = map(int, input().split())
    A = list(map(int, input().split()))
    
    g = gcd(*A)
    for i in range(n):
        A[i] //= g
    
    A_sum = sum(A)
    if A_sum & (A_sum - 1):
        print("No")
        return
    
    n = A_sum.bit_length() - 1
    cnts = [0 for _ in range(n + 1)]
    for a in A:
        for i in range(n):
            if a & (1 << i):
                cnts[i] += 1

    print("Yes")

    m = 1
    to_split = []
    curs = [[] for _ in range(n + 1)]
    curs[n].append(1)
    for i in range(n, -1, -1):
        while len(curs[i]) > cnts[i]:
            to_split.append(curs[i][-1])
            curs[i].pop()
            curs[i - 1].append(m + 1)
            curs[i - 1].append(m + 2)            
            m += 2
    
    print("SPLIT")
    print(len(to_split))
    print(*to_split)
    
    print("DISTRIBUTE")
    for a in A:
        ans = []
        for i in range(n):
            if a & (1 << i):
                ans.append(curs[i][-1])
                curs[i].pop()
        
        print(len(ans))
        print(*ans)        
    
    return

solve()