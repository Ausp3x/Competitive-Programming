def solve():
    n, a, b, p = map(int, input().split())
    
    a %= p
    b %= p
    
    if a == b:
        print((n + 1) * pow(a, n, p) % p)
        return
    
    num = pow(a, n + 1, p) - pow(b, n + 1, p)
    den = pow((a - b) % p, p - 2, p)

    print(num * den % p)
    
    return

t = int(input())
for _ in range(t):
    solve()