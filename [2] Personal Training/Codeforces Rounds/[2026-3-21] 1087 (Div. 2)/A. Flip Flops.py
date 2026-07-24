def solve():
    n, c, k = map(int, input().split())
    A = list(map(int, input().split()))
    
    A.sort(reverse=True)
    
    while len(A) > 0:
        a = A[-1]
        if a > c:
            break

        d = min(c - a, k)
        c += a + d
        k -= d
        
        A.pop()

    print(c)
    
    return

t = int(input())
for _ in range(t):
    solve()