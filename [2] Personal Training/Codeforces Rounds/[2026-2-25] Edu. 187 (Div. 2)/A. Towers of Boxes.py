def solve():
    n, m, d = map(int, input().split())
    
    print((n + d // m) // (d // m + 1))
    
    return

t = int(input())
for _ in range(t):
    solve()