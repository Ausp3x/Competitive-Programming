def solve():
    n = int(input())
    
    ans = []
    for i in range(1, 82):
        if i >= n:
            break
        
        m = list(str(n - i))
        m = sum([int(d) for d in m])
        
        if (m == i):
            ans.append(n - i)

    print(len(ans))
    print(*ans[::-1])    

    return

solve()