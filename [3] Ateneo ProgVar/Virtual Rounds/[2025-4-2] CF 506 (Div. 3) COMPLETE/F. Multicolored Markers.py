from bisect import *
from math import *

def solve():
    a, b = map(int, input().split())
    
    t = a + b    
    ts_mx = isqrt(t)
    T = []
    for i in range(ts_mx, 0, -1):
        if t % i == 0:
            T.append((i, t // i))
        
    as_mx = isqrt(a)
    A = []
    for i in range(1, as_mx + 1):
        if a % i == 0:
            A.append((i, a // i))
    A.sort()
    
    bs_mx = isqrt(b)
    B = []
    for i in range(1, bs_mx + 1):
        if b % i == 0:
            B.append((i, b // i))
    B.sort()
    
    # print(T)
    # print(A)
    # print(B)
    
    for tl, tw in T:
        i_a = bisect_left(A, (tl, tw))
        if i_a > 0:
            i_a -= 1
            l, w = A[i_a]
            if l <= tl and w <= tw:
                print(2 * (tl + tw))
                return
        
        i_b = bisect_left(B, (tl, tw))
        if i_b > 0:
            i_b -= 1
            l, w = B[i_b]
            if l <= tl and w <= tw:
                print(2 * (tl + tw))
                return        
        
    return

solve()