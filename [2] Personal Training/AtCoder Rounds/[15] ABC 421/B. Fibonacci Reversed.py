def solve():
    x, y = input().split()
    
    for i in range(3, 11):
        z = str(int(x) + int(y))[::-1]
        x = y
        y = z
        
    print(int(z))
    
solve()