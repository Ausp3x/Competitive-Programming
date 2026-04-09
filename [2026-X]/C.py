def solve():
    n, m, k = map(int, input().split())
    P = list(map(int, input().split()))
    
    i = -1
    ans = 0
    while i < m - 1:
        i += 1
        l = (P[i] - i - 1) // k * k + 1 
        r = l + k + i - 1
        
        while i + 1 < m:
            if P[i + 1] <= r:
                i += 1
            else:
                break
        
        ans += 1

    print(ans)
            
    return

solve()