def solve():
    n, m = [int(x) for x in input().split()]
    S = [int(x) for x in input().split()]

    S = set(S)
    tot = 0
    for x in range(1, n + 1):
        if x not in S:
            b = bin(x)[2:]
            rem = len(b)
            ans = 0
            cnt = 1
            for j in b[1:]:
                if j == '1':
                    ans += 2 ** (rem - cnt - 1)
                cnt += 1
            tot += ans

    print(tot * 2)
   
solve()