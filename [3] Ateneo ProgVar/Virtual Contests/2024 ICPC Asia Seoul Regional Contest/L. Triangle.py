from math import *

def add(p0, p1):
    return (p0[0] + p1[0], p0[1] + p1[1])

def getArea(p0, p1, p2):
    return abs(p0[0] * p1[1] + p1[0] * p2[1] + p2[0] * p0[1] - 
              (p0[1] * p1[0] + p1[1] * p2[0] + p2[1] * p0[0]))

def solve():
    a, b, c, d, e, f = map(int, input().split())
    
    xy = [(a, b), (c, d), (e, f)]
    dxdy = [[(float('inf'), float('inf')) for j in range(3)] for i in range(3)]
    for i in range(3):
        for j in range(3):
            if i == j:
                continue
            
            dx = xy[j][0] - xy[i][0]
            dy = xy[j][1] - xy[i][1]
            if dx == 0 and dy == 0:
                print(-1)
                return
            
            g = gcd(abs(dx), abs(dy))
            if g == 1:
                print(-1)
                return
            
            dxdy[i][j] = (dx // g, dy // g)
    
    mx = max(getArea(add(xy[0], dxdy[0][1]), add(xy[1], dxdy[1][2]), add(xy[2], dxdy[2][0])),
             getArea(add(xy[0], dxdy[0][2]), add(xy[2], dxdy[2][1]), add(xy[1], dxdy[1][0])))

    mn = float('inf')
    for i in range(3):
        I = []
        for j in range(3):
            if j != i:
                I.append(j)
        
        mn = min(mn,
                 getArea(add(xy[I[0]], dxdy[I[0]][i]), add(xy[I[1]], dxdy[I[1]][i]), add(xy[I[0]], dxdy[I[0]][I[1]])),
                 getArea(add(xy[I[0]], dxdy[I[0]][i]), add(xy[I[1]], dxdy[I[1]][i]), add(xy[I[1]], dxdy[I[1]][I[0]])))
            
    print(mx, mn)

    return 

solve()