def solve():
    N = int(input())
    C = [int(c) for c in input().split()]
    
    c_max = 0
    segments = []
    for i in range(2 * N):
        if C[i] > c_max:
            segments.append([C[i]])
        else:
            segments[-1].append(C[i])
        
        c_max = max(c_max, C[i])
        
    # print(segments)
    
    D = {}
    D[0] = []
    for i in range(len(segments)):
        D_keys = []
        for k in D: 
            D_keys.append(k)
        
        for k in D_keys:
            new_k = k + len(segments[i])
            if new_k not in D:
                D[new_k] = D[k] + [i]
    
    # print(D)
        
    if N not in D:
        print(-1)
        return
    
    chk = [False for i in range(len(segments))]
    for i in D[N]:
        chk[i] = True
    
    A, B = [], []
    for i in range(len(segments)):
        if chk[i]:
            A += segments[i]
        else:
            B += segments[i]        

    print(*A)
    print(*B)

    return

solve()