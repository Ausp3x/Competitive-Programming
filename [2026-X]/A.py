def solve():
    x = int(input())

    A = [3, 0, 2, 1]
    a, b = 0, A[x % 4]
    if A[(x + 1) % 4] < b:
        a, b = 1, A[(x + 1) % 4]
    if A[(x + 2) % 4] < b:
        a, b = 2, A[(x + 2) % 4]
    
    print(a, chr(ord('A') + b))

    return

solve()