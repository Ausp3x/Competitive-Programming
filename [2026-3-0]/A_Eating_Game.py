def solve():
    n = int(input())
    A = list(map(int, input().split()))
    
    a_mx, cnts = -1, {}
    for a in A:
        a_mx = max(a_mx, a)
        if a not in cnts:
            cnts[a] = 1
        else:
            cnts[a] += 1

    print(cnts[a_mx])
    
    return

t = int(input())
for _ in range(t):
    solve()