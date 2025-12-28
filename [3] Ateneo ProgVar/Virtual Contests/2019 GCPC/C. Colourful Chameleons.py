def solve():
    n, c, y = map(int, input().split())
    c -= 1
    X = list(map(int, input().split()))
    
    Y = []
    for i in range(n):
        if i != c:
            Y.append(X[i])
            
    Y.sort()
    
    for i in range(1, n - 1):
        if (Y[i] - Y[i - 1]) % (y + 1) != 0:
            print('impossible')
            return
        
    print(Y[-1], sum(X) + Y[-1] * (y - n + 1))
    
    return

solve()