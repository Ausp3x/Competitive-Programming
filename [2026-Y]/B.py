def solve():
    k = int(input())
    n = input()
    
    s = 0
    for c in n:
        s += ord(c) - ord('0')
        
    if s >= k:
        print(0)
        return
    
    d = abs(k - s)
    
    A = []
    for c in n:
        A.append(ord('9') - ord(c))
        if A[-1] == 0:
            A.pop()
        
    A.sort(reverse=True)
    
    ans = 0
    for a in A:
        if d > 0:
            ans += 1
            d -= a
        else:
            break
        
    print(ans)
    
solve()