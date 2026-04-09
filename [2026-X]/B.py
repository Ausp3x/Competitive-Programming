def solve():
    A = list(input().split())
    
    A.sort()
    
    M = []
    for i in range(1, 10):
        for j in ['m', 'p', 's']:
            M.append([str(i) + j, str(i) + j, str(i) + j])
            if (i + 2 < 10):
                M.append([str(i) + j, str(i + 1) + j, str(i + 2) + j])
    
    # print(M)
    
    ans = 3
    for x in M:
        B = A.copy()
        cur = 3
        for y in x:
            if y in B:
                B.remove(y)
                cur -= 1
                
        ans = min(ans, cur)

    print(ans)                
        
    return

solve()