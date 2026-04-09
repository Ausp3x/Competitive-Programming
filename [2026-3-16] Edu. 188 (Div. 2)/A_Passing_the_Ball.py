def solve():
    n = int(input())
    s = input()

    cur = 0    
    vst = [False for _ in range(n)]
    vst[cur] = True
    while True:
        nxt = cur + (-1 if s[cur] == 'L' else 1)
        if vst[nxt]:
            break
    
        cur = nxt
        vst[nxt] = True
        
    print(sum(vst))
    
    return

t = int(input())
for _ in range(t):
    solve()