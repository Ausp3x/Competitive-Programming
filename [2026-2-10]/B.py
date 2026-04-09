def solve():
    a, b = map(int, input().split())
    
    req = {
        '0': 6, '1': 2, '2': 5, '3': 5, '4': 4, 
        '5': 5, '6': 6, '7': 3, '8': 7, '9': 6
    }
    
    ans = 0
    for i in range(a, b + 1):
        for c in str(i):
            ans += req[c]
    
    print(ans)        
    
    return

solve()