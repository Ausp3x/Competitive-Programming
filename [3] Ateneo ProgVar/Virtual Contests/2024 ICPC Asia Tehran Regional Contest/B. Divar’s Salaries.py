def solve():
    n = int(input())
    for _ in range(n):
        x, k, h = map(int, input().split())
        
        n = min(k - h, 140)
        o = k - h - n
        
        ans = x * n + x * o * 3 // 2 + x * h * 2
        
        if ans == 0:
            print(0)
            continue
        
        parts = []
        while ans > 0:
            parts.append(ans % 1000)
            ans //= 1000
            
        parts.reverse()
        
        print(parts[0], end='')
        for i in range(1, len(parts)):
            print(',', end='')
            print(str(parts[i]).zfill(3), end='')
        print()
        
    return

solve()