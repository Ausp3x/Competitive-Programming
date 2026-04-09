def solve():
    s, v1, v2, t1, t2 = list(map(int, input().split()))
    
    a = t1 + s * v1 + t1
    b = t2 + s * v2 + t2
    
    if a == b:
        print('Friendship')
        return 
    
    print('First' if a < b else 'Second')
    
    return

solve()