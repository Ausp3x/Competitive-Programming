def solve():
    n = int(input())
    ans = 0
    for _ in range(n):
        s = input()
        ans += s == 'Takahashi'
        
    print(ans)
    
    return

solve()