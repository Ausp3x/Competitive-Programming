def solve():
    n = int(input())
    A = list(map(int, input().split()))
    
    B = dict()
    for a in A:
        if a not in B:
            B[a] = 1
        else:
            B[a] += 1    
    
    C = []
    for u, v in B.items():
        C.append(v)
        
    C.sort()
        
    ans = 0
    for i in range(1, n + 1):
        cur = 0
        for c in C:
            cur += c >= i
        
        ans = max(ans, i * cur)
        
    print(ans)
    
    return

t = int(input())
for _ in range(t):
    solve()