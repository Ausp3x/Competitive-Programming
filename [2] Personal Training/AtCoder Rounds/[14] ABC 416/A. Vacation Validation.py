def solve():
    n, l, r = map(int, input().split())
    s = input()
    
    if 'x' in s[l-1:r]:
        print('No')
    else:
        print('Yes')
    
    return

solve()