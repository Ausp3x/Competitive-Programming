def solve():
    s, m = map(int, input().split())
    
    l, r = 0, 1000000000000000001
    while r - l > 1:
        md = (l + r) // 2
                 
        t = s
        for i in range(60, -1, -1):
            if not m & (1 << i):
                continue
            
            d = min(t // (1 << i), md)
            t -= d * (1 << i)
            
        if t > 0:
            l = md
        else:
            r = md
        
    print(r if r < 1000000000000000001 else -1)
    
    return

t = int(input())
for _ in range(t):
    solve()