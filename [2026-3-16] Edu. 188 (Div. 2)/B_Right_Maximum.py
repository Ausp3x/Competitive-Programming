def solve():
    n = int(input())
    A = list(map(int, input().split()))
    
    mx, ans = -1, 0
    for a in A:
        if a >= mx:
            mx = a
            ans += 1
            
    print(ans)
    
    return

t = int(input())
for _ in range(t):
    solve()