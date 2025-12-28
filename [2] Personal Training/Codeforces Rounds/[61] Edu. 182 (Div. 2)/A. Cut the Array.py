def solve():
    n = int(input())
    A = list(map(int, input().split()))
    
    for i in range(n):
        for j in range(i + 1, n):
            x = sum(A[0:i + 1]) % 3
            y = sum(A[i + 1:j + 1]) % 3
            z = sum(A[j + 1:n]) % 3
            
            if (x == y and x == z and y == z) or (x != y and x != z and y != z):
                print(i + 1, j + 1)
                return
            
    print('0 0')
    
    return

t = int(input())
for _ in range(t):
    solve()