def solve():
    n, k, m = map(int, input().split())
    A = list(map(int, input().split()))
    
    M = [[] for i in range(m)]
    for a in A:        
        M[a % m].append(a)
        
    for i in range(m):
        if len(M[i]) >= k:
            print('Yes')
            print(*M[i][:k])
            return
        
    print('No')
   
    return
    
solve()