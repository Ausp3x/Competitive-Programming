def solve():
    n = int(input())
    A = list(map(int, input().split()))

    m = n
    for i in range(n):
        if A[i] == m:
            m -= 1
        else:
            break
    
    if m == 0:
        print(*A)
        return
    
    # print(m)
        
    for i in range(n):
        if A[i] == m:
            print(*A[:n-m], *A[n-m:i+1][::-1], *A[i+1:])
            return
    
    return

t = int(input())
for _ in range(t):
    solve()