pows = [2 ** i for i in range(1, 48)]

def solve():
    s = input()
    
    if len(s) == 0:
        print('INVALID')
        return
    
    for c in s:
        if c != 'E' and c != 'O':
            print('INVALID')
            return
    
    if s[-1] != 'O':
        print('INVALID')
        return
    
    if 'OO' in s:
        print('INVALID')
        return
    
    s = s[::-1]
    ans = float('inf')
    for p in pows:
        cur = p
        for c in s:
            if c == 'O':
                if (cur - 1) % 3 != 0:
                    cur = float('inf')
                    break                
                
                cur = (cur - 1) // 3
                
                if cur == 1:
                    cur = float('inf')
                    break
            elif c == 'E':
                cur *= 2
        
        ans = min(ans, cur)
        
    print('INVALID' if ans == float('inf') else ans)
    
    
solve()