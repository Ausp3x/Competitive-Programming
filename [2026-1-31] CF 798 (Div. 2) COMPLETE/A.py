def solve():
    n, m, k = map(int, input().split())
    a = input()
    b = input()
    
    a = ''.join(sorted(a))
    b = ''.join(sorted(b))
    
    # print(a, b)
    
    i, j = 0, 0
    ctr = [0, 0]
    ans = ''
    while i < n and j < m:
        if a[i] < b[j]:
            if ctr[0] < k:
                ans += a[i]
                i += 1
                ctr[0] += 1
                ctr[1] = 0
            else:
                ans += b[j]
                j += 1
                ctr[1] += 1
                ctr[0] = 0
        else:
            if ctr[1] < k:
                ans += b[j]
                j += 1
                ctr[1] += 1
                ctr[0] = 0
            else:
                ans += a[i]
                i += 1
                ctr[0] += 1
                ctr[1] = 0

    print(ans)

    return

t = int(input())
for _ in range(t):
    solve()