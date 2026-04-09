def solve():
    n = int(input())
    A = list(map(int, input().split()))
    s = input()
    
    cnt = {}
    for i in range(n):
        if A[i] not in cnt:
            cnt[A[i]] = [s[i]]
        else:
            cnt[A[i]].append(s[i])
            
    for x, y in cnt.items():
        if len(set(y)) > 1:
            print('NO')
            return
        
    print('YES')
    
    return

t = int(input())
for _ in range(t):
    solve()