def solve():
    x, n = map(int, input().split())
    
    print(x * (n % 2))
    
    return

t = int(input())
for _ in range(t):
    solve()