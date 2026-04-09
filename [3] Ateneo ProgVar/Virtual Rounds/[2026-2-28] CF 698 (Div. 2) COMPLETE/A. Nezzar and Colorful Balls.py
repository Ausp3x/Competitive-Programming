def solve():
    n = int(input())
    A = list(map(int, input().split()))
    
    ans, cnts = 0, {}
    for a in A:
        if a not in cnts:
            cnts[a] = 1
        else:
            cnts[a] += 1
            
        ans = max(ans, cnts[a])
            
    print(ans)
            
    return

t = int(input())
for _ in range(t):
    solve()