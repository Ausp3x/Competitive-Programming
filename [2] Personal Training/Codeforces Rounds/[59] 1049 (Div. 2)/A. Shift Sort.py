def solve():
    n = int(input())
    s = input()
    
    cnt, ans = n - s.count('1'), 0
    for i in range(cnt):
        ans += s[i] == '1'
            
    print(ans)
    
    return

t = int(input())
for _ in range(t):
    solve()