def solve():
    n = int(input())
    s = 'X' + input()
    
    ans = 0
    A = [0 for _ in range(n + 1)]
    for i in range(1, n + 1):
        if s[i] == '*':
            continue
        
        if i >= 2:
            if s[i - 1] == '*' and s[i - 2] == '*':
                break
        
        A[i] = max(A[i], A[i - 1] + (s[i] == '@'))
        if i >= 2:
            A[i] = max(A[i], A[i - 2] + (s[i] == '@'))

        ans = max(ans, A[i])
    
    # print(A)    
    print(ans)
        
    return

t = int(input())
for _ in range(t):
    solve()