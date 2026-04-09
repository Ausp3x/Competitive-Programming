def solve():
    n, k, t = map(int, input().split())
    
    if t <= n:
        print(min(k, t))
    else:
        print(max(k - t + n, 0))
    
    return

solve()