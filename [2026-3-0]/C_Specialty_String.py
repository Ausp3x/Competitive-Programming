def solve():
    n = int(input())
    A = list(input())
    
    while len(A) > 1:
        chk = False
        for i in range(len(A) - 1):
            if A[i] == A[i + 1]:
                A = A[:i] + A[i+2:]
                chk = True
                break
        
        if not chk:
            break
        
    print('YES' if len(A) == 0 else 'NO')
    
    return

t = int(input())
for _ in range(t):
    solve()