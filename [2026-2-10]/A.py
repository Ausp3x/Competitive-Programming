def solve():
    x, y = map(int, input().split())
    X, Y = map(int, input().split())
    
    print(abs(X - x) + abs(Y - y) - min(abs(X - x), abs(Y - y)))
    
    return

solve()