def solve():
    k = int(input()) 
    S = [input() for _ in range(k)]
    T = list(map(int, input().split()))
    
    timer = 1
    is_inline = False
    is_emoji = False
    prv_backslash = False
    cnts = [0, 0]
    A, B = [], []
    for i in range(k):
        for c in S[i]:
            if is_inline:
                if c == '`':
                    is_inline = False
                else:
                    A.append(timer)
                    B.append(T[i])
                    timer += 1
                continue
            
            if is_emoji:
                if c == ':':
                    is_emoji = False
                    A.append(timer)
                    B.append(T[i])
                    timer += 1
                continue
            
            if prv_backslash:
                prv_backslash = False
                A.append(timer)
                B.append(T[i])
                timer += 1
                continue        
            
            if c == '\\':
                prv_backslash = True
                continue
            
            if c == ':':
                is_emoji = True
                continue
            
            if c == '`':
                is_inline = True
                continue
             
            if c == '(' or c == '[':
                cnts[c == '['] += 1
                if cnts[0] + cnts[1] > 1:
                    A.append(timer)
                    B.append(T[i])
                    timer += 1
                continue
            
            if c == ')' or c == ']':
                cnts[c == ']'] -= 1
                if cnts[0] + cnts[1] > 0:
                    A.append(timer)
                    B.append(T[i])
                    timer += 1
                continue
                
            A.append(timer)
            B.append(T[i])
            timer += 1
    
    ans = 1                    
    for i in range(len(A)):
        ans = max(ans, B[i] - A[i])
        
    print(ans + 1)
    
    return

solve()