def calc(n, p, m):
    res = m * p / (n + m - p + 1)
    for i in range(p - 1):
        res *= (n - i) / (n + m - i)
        
    return res

def solve():
    n, p = map(int, input().split())

    m = 1
    ans = calc(n, p, m)
    while True:
        cur = ans
        cur *= (m + 1) / m
        cur *= (n + m - p + 1) / (n + m + 1)
        
        if cur > ans:
            m += 1
            ans = cur
        else:
            break
            
    print(ans)
    
    return

solve()