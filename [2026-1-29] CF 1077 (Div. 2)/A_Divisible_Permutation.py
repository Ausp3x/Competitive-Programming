def solve():
    n = int(input())
    
    j = 1
    ans = [-1 for _ in range(n)]
    for i in range(n - 1, -1, -2):
        ans[i] = j
        j += 1
    for i in range(n % 2, n, 2):
        ans[i] = j
        j += 1
        
    print(*ans)     

    return

t = int(input())
for _ in range(t):
    solve()