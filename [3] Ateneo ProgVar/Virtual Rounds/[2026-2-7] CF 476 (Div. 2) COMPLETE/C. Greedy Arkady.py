def solve():
    n, k, M, D = map(int, input().split())
    
    ans = 0
    for d in range(1, D + 1):
        l, r = 0, M + 1
        while r - l > 1:
            md = (l + r) // 2
            
            if (n // md + k - 1) // k < d:
                r = md
            else:
                l = md
        
        if l == 0:
            continue
        
        # print((n // l + k - 1) // k, d, l, r)
        if (n // l + k - 1) // k != d:
            continue
           
        ans = max(ans, d * l)
    
    print(ans)
    
    return

solve()