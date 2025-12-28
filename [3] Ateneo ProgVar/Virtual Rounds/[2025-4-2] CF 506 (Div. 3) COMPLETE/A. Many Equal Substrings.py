def solve():
    n, k = map(int, input().split())
    s = input()
    
    k -= 1
    ans = s
    while k > 0:
        for i in range(n - 1, -1, -1):
            if ans[len(ans)-i:] == s[:i]:
                ans += s[i:]
                break                
        
        k -= 1
        
    print(ans)
    
    return

solve()