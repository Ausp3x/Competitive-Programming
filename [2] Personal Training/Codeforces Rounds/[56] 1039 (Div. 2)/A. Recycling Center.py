def solve():
    n, c = map(int, input().split())
    A = list(map(int, input().split()))
    
    A.sort()
    
    ans, k = n, n - 1
    for i in range(0, n):
        while A[k] > c and k >= 0:
            k -= 1
            
        ans -= k >= 0
        k -= 1

        for j in range(n):
            A[j] *= 2
        
    print(ans)
    
    return

t = int(input())
for _ in range(t):
    solve()