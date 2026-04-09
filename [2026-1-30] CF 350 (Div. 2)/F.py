def solve():
    s = input()
    t = input()
    
    n = len(s)
    m = len(t)
    cnts = [0 for _ in range(10)]
    for c in s:
        cnts[int(c)] += 1
    for c in t:
        cnts[int(c)] -= 1
    
    for i in range(m, n):
        if n - len(str(i)) != i:
            continue
        
        has_neg = False
        for c in set(str(i)):
            if str(i).count(c) > cnts[int(c)]:
                has_neg = True
                break
            
        if has_neg:
            continue
        
        add_first = len(t) == 1
        if len(t) > 1:
            add_first = t + t[0] < t[0] + t
            
        for c in str(i):
            cnts[int(c)] -= 1
        
        u = t
        for j in range(10):
            if cnts[j] > 0:
                u += str(j) * cnts[j]
        
        v = ''
        for j in range(1, 10):
            if cnts[j] > 0:
                v = str(j)
                cnts[j] -= 1
                break
        
        for j in range(10):
            if int(t[0]) == j and add_first:
                v += t
                
            if cnts[j] > 0:
                v += str(j) * cnts[j]
                
            if int(t[0]) == j and not add_first:
                v += t

        # print(u, v)
        if u[0] == '0':
            print(v)
        elif v[0] == '0':
            print(u)
        else:
            print(u if u < v else v)
                
        return
    
    return

solve()