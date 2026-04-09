def solve():
    x, y = map(int, input().split())
    
    print('Yes' if -3 <= y - x <= 2 else 'No')
    
solve()