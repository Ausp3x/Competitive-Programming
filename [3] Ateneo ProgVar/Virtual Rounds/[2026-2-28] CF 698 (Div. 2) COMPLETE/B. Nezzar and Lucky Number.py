L = [[float('inf') for _ in range(i)] for i in range(10)]

def solve():
    global L
    q, d = map(int, input().split())
    A = list(map(int, input().split()))
    
    for a in A:
        if a < L[d][a % d]:
            print('NO')
        else:
            print('YES')    
    
    return

for i in range(1, 100):
    A = [int(x) for x in set(list(str(i)))]
    for a in A:
        if a == 0:
            continue
        
        if i < L[a][i % a]:
            L[a][i % a] = i

# for l in L:
#     print(l)

t = int(input())
for _ in range(t):
    solve()