def solve():
    a, b, c, x, y = map(int, input().split())
    
    x -= min(x, a)
    y -= min(y, b)
    
    print('YES' if x + y <= c else 'NO')
    
    return

t = int(input())
for _ in range(t):
    solve()