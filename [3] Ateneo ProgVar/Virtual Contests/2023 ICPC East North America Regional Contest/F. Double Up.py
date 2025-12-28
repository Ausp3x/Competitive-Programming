n = int(input())
A = [int(a) for a in input().split()]
# print(A)

ans, cur = 0, 1
B = []
for _ in range(120):
    if len(A) > 0:
        ans = cur
    
    i = 0
    while i < len(A):
        if i + 1 < len(A):
            if A[i] == cur and A[i] == A[i + 1]:
                B.append(2 * A[i])
                i += 2
                continue
        
        if A[i] != cur:
            B.append(A[i])
        i += 1
    # print(B)
    
    cur *= 2
    A = B
    B = []
    
print(ans)