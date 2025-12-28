def solve():
    n = int(input())
    A = list(map(int, input().split()))
    
    for i in range(1, n + 1):
        if A[0] != i and A[-1] != i:
            print('NO')
            return
        
        if A[0] == i:
            A = A[1:]
        else:
            A = A[:-1]
        
    print('YES')
    
    return

t = int(input())
for _ in range(t):
    solve()