def solve():
    n, k = map(int, input().split())
    grid = [list(input()) for _ in range(n)]
    
    cnt = [[0 for j in range(n)] for i in range(n)]
    for i in range(n - k + 1):
        for j in range(n):
            s = ''
            for l in range(i, i + k):
                s += grid[l][j]
                
            if s != '.' * k:
                continue
            
            for l in range(i, i + k):
                cnt[l][j] += 1
                
    for j in range(n - k + 1):
        for i in range(n):
            s = ''
            for l in range(j, j + k):
                s += grid[i][l]
            
            if s != '.' * k:
                continue
            
            for l in range(j, j + k):
                cnt[i][l] += 1
            
    mx = -1
    ans = (-1, -1)
    for i in range(n):
        for j in range(n):
            if mx < cnt[i][j]:
                mx = cnt[i][j]
                ans = (i + 1, j + 1)
    
    print(*ans)
    
    return

solve()