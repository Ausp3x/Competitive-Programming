def solve():
    m, b, s = map(int, input().split())
    chks = [False for _ in range(s + 1)]
    for _ in range(b):
        route = 'X' + input()
        if route[m] == '0':
            continue
        
        for i in range(1, s + 1):
            if i == m:
                continue
            
            chks[i] |= route[i] == '1' 
            
    print(sum(chks))
    
    return

solve()