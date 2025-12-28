from math import *

def solve():
    n, m, f = input().split()
    n = int(n)
    m = int(m)
    f = float(f)
    
    def P(m, f, d):
        return m - d * d * f * f
    
    def E(m, f, d):
        return P(m, f, d) / (n - d)
    
    ans = 0
    for d in range(0, n):
        # print(f"{d}: {E(m, f, d)}")
        if E(m, f, d) > ans:
            ans = E(m, f, d)
        else:
            break
        
    print(f'{ans:.9f}')
        
    return

solve()