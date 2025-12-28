def solve():
    s = list(input())
    
    t = s.copy()
    if t[0] == '.':
        t[0] = 'o'
    
    n = len(s)
    for i in range(0, n - 1):
        if t[i] == '#':
            if t[i + 1] == '.':
                t[i + 1] = 'o'
                
    print(''.join(t))
            
    return

solve()