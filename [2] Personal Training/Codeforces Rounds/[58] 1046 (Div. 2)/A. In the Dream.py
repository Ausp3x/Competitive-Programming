def solve():
    a, b, c, d = map(int, input().split())
    c -= a
    d -= b
    if a > 2 * b + 2 or b > 2 * a + 2 or c > 2 * d + 2 or d > 2 * c + 2:
        print("NO")
        return
    
    print("YES")
    
    return

t = int(input())
for _ in range(t):
    solve()