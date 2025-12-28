from math import *

def solve():
    n = int(input())
    
    cnt, cur = 0, 0
    while 2 * cur + 1 < n:
        cnt += 1
        cur = 2 * cur + 1
        
    print(2 * cnt + 3) 

    return

t = int(input())
for _ in range(t):
    solve()