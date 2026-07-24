def solve():
    x, y = map(int, input().split())

    X = 0
    if y < 0:
        X += 4 * abs(y)
    elif y > 0:
        X += 2 * y
        
    print('YES' if x - X >= 0 and (x - X) % 3 == 0 else 'NO')
        
    return

t = int(input())
for _ in range(t):
    solve()