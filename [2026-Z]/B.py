def solve():
    s = input()
    
    cnt, ans = 0, '?'
    for c in 'abcdefghijklmnopqrstuvwxyz'[::-1]:
        cur = s.count(c)
        if cur >= cnt:
            cnt = cur
            ans = c
    
    print(ans)
    
    return

solve()