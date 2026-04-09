def solve():
    n = int(input())
    Q = list(map(int, input().split()))
    A = list(map(int, input().split()))
    B = list(map(int, input().split()))

    a_max = 1000005
    for i in range(n):
        if A[i] == 0:
            continue
        
        a_max = min(a_max, Q[i] // A[i])
    
    b_max = 1000005
    for i in range(n):
        if B[i] == 0:
            continue
        
        b_max = min(b_max, Q[i] // B[i])    
    
    ans = 0
    for a in range(a_max + 1):   
        b = b_max
        for i in range(n):
            if B[i] == 0:
                continue
            
            b = min(b, max(Q[i] - a * A[i], 0) // B[i])
            
        ans = max(ans, a + b)

    print(ans)

    return

solve()