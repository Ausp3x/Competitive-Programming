def solve():
    n, a, b = map(int, input().split())
    
    if b < 2 * a:
        print(n // 2 * b + n % 2 * a)
    else:
        print(n * a)
    
    return

t = int(input())
for _ in range(t):
    solve()