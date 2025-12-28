def solve():
    N = int(input())
    A = [int(a) for a in input().split()]
    
    b = max(A)
    s = sum(A)
    
    if b >= 2 * (s - b):
        print(s - b)
    else:
        print(s // 3)

    return

solve()