def solve():
    x = int(input())
    
    y = 2 * x
    assert(int(str(x) + str(y)) % (x + y) == 0)
    
    print(y)
    
    return

t = int(input())
for _ in range(t):
    solve()