def solve():
    n = int(input())
    A = [input() for _ in range(n)]
    
    x, y = input().split()
    x = int(x)
    
    print('Yes' if A[x - 1] == y else 'No')
    
    return

solve()