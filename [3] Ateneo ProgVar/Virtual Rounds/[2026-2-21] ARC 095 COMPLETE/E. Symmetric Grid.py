def solve():
    n, m = map(int, input().split())
    G = [list(input()) for _ in range(n)]
    
    A = []
    def calc(msk, cur, mid):
        if len(cur) == n // 2:
            A.append(cur.copy())
            if mid != -1:
                A[-1].append(mid)
            return
        
        I = []
        for i in range(n):
            if not msk & (1 << i):
                I.append(i)
                
        siz = len(I)
        for j in range(1, siz):
            cur.append((I[0], I[j]))
        
            calc(msk | (1 << I[0]) | 1 << I[j], cur, mid)
            
            cur.pop()
    
    if n % 2 == 0:
        calc(0, [], -1)
    else:
        for i in range(n):
            calc(1 << i, [], i)
    
    palin = [False for _ in range(n)]
    for i in range(n):
        cnt = {}
        for j in range(m):
            if G[i][j] not in cnt:
                cnt[G[i][j]] = 1
            else:
                cnt[G[i][j]] += 1
                
        odd = 0
        for c in cnt:
            odd += cnt[c] % 2
            
        palin[i] = odd == m % 2
    
    for a in A:
        # print(a)
        
        order = [-1 for _ in range(n)]
        for i in range(n // 2):
            order[a[i][0]] = i
            order[a[i][1]] = n - i - 1
        if n % 2 != 0:
            order[a[-1]] = n // 2
        
        G2 = [['?' for j in range(n)] for i in range(m)]
        for i in range(n):
            for j in range(m):
                G2[j][order[i]] = G[i][j]
                
        cnt = {}
        for i in range(m):
            r = ''.join(G2[i])
            # print(r)
            if r not in cnt:
                cnt[r] = [i]
            else:
                cnt[r].append(i)   
    
        vst = [False for _ in range(m)]
        for i in range(m):
            r = ''.join(G2[i])
            s = r[::-1]        
            if vst[i] or r not in cnt or s not in cnt:
                continue
            
            if len(cnt[s]) == 0 or (r == s and len(cnt[r]) < 2):
                continue
                        
            vst[i] = True
            cnt[r].remove(i)
            vst[cnt[s][-1]] = True
            cnt[s].pop()            
                
        if sum(vst) != m - m % 2:
            continue
        
        ok = True
        if m % 2 != 0:
            for i in range(m):
                if vst[i]:
                    continue
                
                if G2[i] != G2[i][::-1]:
                    ok = False
            
                break
            
        if ok:
            print('YES')
            return
        
    print('NO')
            
    return

solve()