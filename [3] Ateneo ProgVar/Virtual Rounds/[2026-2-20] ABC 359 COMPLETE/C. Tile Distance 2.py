def solve():
    sx, sy = map(int, input().split())
    tx, ty = map(int, input().split())
    
    e = (sx + sy) % 2 == 0
    o = (sx + sy) % 2
    x = abs(tx - sx)
    y = abs(ty - sy)

    if tx <= sx:
        print((max(x - y - o, 0) + 1) // 2 + y)
    else:
        print((max(x - y - e, 0) + 1) // 2 + y)
    
    return

solve()