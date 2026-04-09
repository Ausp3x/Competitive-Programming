from bisect import bisect_left

def solve():
    A = []
    for i in range(100, 1000):
        j = str(i)
        if (ord(j[0]) - ord('0')) * (ord(j[1]) - ord('0')) == (ord(j[2]) - ord('0')):
            A.append(i)
            
    n = int(input())
            
    print(A[bisect_left(A, n)])
    
solve()