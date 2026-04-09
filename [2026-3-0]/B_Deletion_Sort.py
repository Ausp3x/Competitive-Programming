def solve():
    n = int(input())
    A = list(map(int, input().split()))
    
    B = A.copy()
    B.sort()
    
    if A == B:
        print(len(A))
        return
    
    print(1)
    
    return

t = int(input())
for _ in range(t):
    solve()