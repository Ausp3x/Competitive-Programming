def solve():
    n = int(input())
    A = list(map(int, input().split()))
    
    for i in range(n):
        if A[i] == n:
            A[0], A[i] = A[i], A[0]
            
    print(*A)
    
    return

t = int(input())
for _ in range(t):
    solve()