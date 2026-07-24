def solve():
    h, w = map(int, input().split())
    
    print('Yes' if 10000 * w >= 25 * h * h else 'No')
    
    return

solve()