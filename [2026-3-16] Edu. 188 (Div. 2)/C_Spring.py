from math import *

def solve():
    a, b, c, m = map(int, input().split())
    
    ab = a * b // gcd(a, b)
    ac = a * c // gcd(a, c)
    bc = b * c // gcd(b, c)
    abc = ab * c // gcd(ab, c)

    n_a = m // a
    n_b = m // b
    n_c = m // c
    n_ab = m // ab
    n_ac = m // ac
    n_bc = m // bc
    n_abc = m // abc

    A = 2 * n_abc + 3 * (n_ab - n_abc) + 3 * (n_ac - n_abc) + 6 * (n_a - n_ab - n_ac + n_abc)
    B = 2 * n_abc + 3 * (n_ab - n_abc) + 3 * (n_bc - n_abc) + 6 * (n_b - n_ab - n_bc + n_abc)
    C = 2 * n_abc + 3 * (n_ac - n_abc) + 3 * (n_bc - n_abc) + 6 * (n_c - n_ac - n_bc + n_abc)

    print(A, B, C)
    
    return

t = int(input())
for _ in range(t):
    solve()