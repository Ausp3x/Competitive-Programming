from math import *

def solve():
    n = int(input())
    
    if n == 1:
        print('1 bit')
        return

    ans = 1
    while n > (1 << ans) - 1:
        ans <<= 1
        
    print(f'{ans} bits')

    return

solve()