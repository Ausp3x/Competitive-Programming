def solve():
    n = int(input())
    A = list(map(int, input().split()))
    
    B = [[] for _ in range(n + 1)]
    for i in range(2 * n):
        B[A[i]].append(i)
        
    # print(B)
        
    ans = 0
    for i in range(n + 1):
        if len(B[i]) == 0:
            continue
        
        ans += B[i][1] - B[i][0] == 2

    print(ans)
    
    return

solve()