def solve():
    k, x, a = list(map(int, input().split()))
    
    t, B = 1, [0 for _ in range(x + 1)]
    B[0] = 1
    for i in range(1, x + 1):
        B[i] = t // (k - 1) + 1
        t += B[i]
    
    # print(t)    
    # print(B)
    
    print('YES' if t <= a else 'NO')
    
    return

t = int(input())
for _ in range(t):
    solve()