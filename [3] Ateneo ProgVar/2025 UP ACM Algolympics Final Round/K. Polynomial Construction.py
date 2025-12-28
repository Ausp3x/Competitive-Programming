def getCoef(R: list):
    n = len(R)
    for i in range(n):
        R[i] = -R[i]
    
    res = [0 for _ in range(n + 1)]
    for msk in range(0, 1 << n):
        cnt, cur = 0, 1
        for i in range(0, n):
            if msk & (1 << i):
                cnt += 1
                cur *= R[i]

        res[cnt] += cur

    res.reverse()

    return res

def incDeg(n, R: list):
    res = R.copy()
    res.reverse()
    res.extend([0 for _ in range(n)])
    res.reverse()
    
    return res

def mul(x, R: list):
    res = R.copy()
    for i in range(len(res)):
        res[i] *= x
        
    return res

def pad(n, R: list):
    res = R.copy()
    res.extend([0 for _ in range(n)])
    
    return res

def solve():
    n, m, k = map(int, input().split())
    C = list(map(int, input().split()))
    R = list(map(int, input().split()))

    base, L = getCoef(R), (n + 1) * (m + 1)
    ans = incDeg((n + 1) * (m + 1), base)
    for i in range(n, 0, -1):
        cur = incDeg(i * (m + 1), base)
        cur = mul(C[n - i], pad(L - len(cur), cur))
        assert(len(cur) == L)
        for j in range(L):
            ans[j] += cur[j]
        # print(C[n - i], ans[i + m + 1], cur, ans)
            
    for i in range(k):
        cur = ans.copy()
        cur_add = pad(L - len(base), mul(i, base))
        assert(len(cur_add) == L)
        for j in range(L):
            cur[j] += cur_add[j]
            
        print(len(cur) - 1)
        print(*cur)
    
    return

solve()