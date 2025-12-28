def solve():
    n, k = map(int, input().split())
    
    ans = ['0' for _ in range(n)]
    for i in range(k):
        ans[i] = '1'
        
    print(''.join(ans))
    
t = int(input())
for _ in range(t):
    solve()