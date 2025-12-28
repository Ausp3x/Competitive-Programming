from math import ceil

def solve():
    n, k = [int(x) for x in input().split()]
    if k < n // 2 or n == k:
        print(-1)
        return
        
    if k == n // 2:
        t = n // 2
        mid = ""
        
        for x in range(t):
            mid += "(" 
        for x in range(t):
            mid += (")")
        print(mid)
    else:
        excess = k - n // 2
        t = n - k
        mid = ""
        
        for x in range(t):
            mid += "(" 
        for x in range(t):
            mid += (")")
        print("()" * ceil(excess / 2) + mid + "()" * (excess // 2))
        
    return

solve()