def solve():
    n, w = map(int, input().split())
    
    print(n // w * (w - 1) + n % w)
    
    return

t = int(input())
for _ in range(t):
    solve()