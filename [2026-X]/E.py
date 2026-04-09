def solve():
    n, k = map(int, input().split())
    s = 'X' + input() + 'X'
    
    prf = [[0 for _ in range(n + 2)], [0 for _ in range(n + 2)]]
    for i in range(1, n + 1):
        prf[0][i] = prf[0][i - 1]
        prf[1][i] = prf[1][i - 1]
        prf[ord(s[i]) - ord('0')][i] = i
    prf[0][n + 1] = prf[0][n]
    prf[1][n + 1] = prf[1][n]
    
    suf = [[n + 1 for _ in range(n + 2)], [n + 1 for _ in range(n + 2)]]
    for i in range(n, 0, -1):
        suf[0][i] = suf[0][i + 1]
        suf[1][i] = suf[1][i + 1]
        suf[ord(s[i]) - ord('0')][i] = i
    suf[0][0] = suf[0][1]
    suf[1][0] = suf[1][1]
    
    if prf[0][n + 1] - suf[0][0] <= k - 1 or prf[1][n + 1] - suf[1][0] <= k - 1:
        print('tokitsukaze')
        return
    
    for i in range(1, n - k + 2):
        l0, r0, l1, r1 = suf[0][0], prf[0][n + 1], suf[1][0], prf[1][n + 1]
        l0 = min(l0, i)
        r0 = max(r0, i + k - 1)
        if suf[1][0] >= i:
            l1 = suf[1][i + k]
        if prf[1][n + 1] <= i + k - 1:
            r1 = prf[1][i - 1]

        if (not r0 - l0 <= k - 1) and (not r1 - l1 <= k - 1):
            print('once again')
            return
        
        l0, r0, l1, r1 = suf[0][0], prf[0][n + 1], suf[1][0], prf[1][n + 1]
        l1 = min(l1, i)
        r1 = max(r1, i + k - 1)
        if suf[0][0] >= i:
            l0 = suf[0][i + k]
        if prf[0][n + 1] <= i + k - 1:
            r0 = prf[0][i - 1]

        if (not r0 - l0 <= k - 1) and (not r1 - l1 <= k - 1):
            print('once again')
            return
        
    print('quailty')     
    
    return

solve()