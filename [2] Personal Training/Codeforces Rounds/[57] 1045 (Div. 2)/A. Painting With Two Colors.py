def solve():
    n, a, b = map(int, input().split())
    if b > a:
        print('YES' if b % 2 == n % 2 else 'NO')
    else:
        print('YES' if a % 2 == n % 2 and b % 2 == n % 2 else 'NO')
    
    return

t = int(input())
for _ in range(t):
    solve()