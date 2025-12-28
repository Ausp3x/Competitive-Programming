def solve():
    n, m = map(int, input().split())
    words = [input() for _ in range(n)]
    
    ans = 0
    for j in range(m):
        cnts = [0 for _ in range(26)]
        for i in range(n):
            cnts[ord(words[i][j]) - ord('a')] += 1
            
        mx_cnt = max(cnts)
        ans += n - mx_cnt
        
    print(ans)
            
solve()