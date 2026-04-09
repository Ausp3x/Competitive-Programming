def solve():
    n, s, x = map(int, input().split())
    A = list(map(int, input().split()))
    
    if sum(A) > s:
        print('NO')
        return
    
    print('YES' if (s - sum(A)) % x == 0 else 'NO')
    
    return

t = int(input())
for _ in range(t):
    solve()