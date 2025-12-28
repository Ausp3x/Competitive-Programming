def solve():
    n = int(input())
    A, longest = [], []
    for i in range(2 * n - 2):
        s = input()
        
        A.append(s)
        if len(s) == n - 1:
            longest.append(s)
    
    Q = [longest[0] + longest[1][-1], longest[1] + longest[0][-1]]
    for S in Q:
        prf, suf = set(), set()
        for i in range(n - 1):
            prf.add(S[0:i + 1])
            suf.add(S[i + 1:])
            
        assert(len(prf) == len(suf))            

        chk = True
        ans = ['_' for _ in range(2 * n - 2)]
        for i in range(2 * n - 2): 
            if A[i] in prf:
                ans[i] = 'P'
                prf.remove(A[i])
            elif A[i] in suf:
                ans[i] = 'S'
                suf.remove(A[i])
            else:
                chk = False
                break
            
        if chk:
            print(''.join(ans))
            return
            
    print(-1)
    
    return

solve()
