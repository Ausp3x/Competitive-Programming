def sum_digits(x):
    res, y = 0, str(x)
    for c in y:
        res += ord(c) - ord('0')
        
    return res

def solve():
    x = int(input())
    
    y = list(map(int, list(str(x))))
    y[0] -= 1
    y.sort()
    
    ans, k = 0, sum_digits(x)
    while k > 9:
        ans += 1
        k -= y[-1]
        y.pop()
    
    print(ans)
    
    return

t = int(input())
for _ in range(t):
    solve()