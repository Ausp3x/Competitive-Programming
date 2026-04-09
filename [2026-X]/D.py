def solve():
    n = int(input())
    A = list(map(int, input().split()))
    
    A.sort()
    
    cnts = {}
    for a in A:
        if a not in cnts:
            cnts[a] = 1
        else:
            cnts[a] += 1
        
        if cnts[a] > 2:
            print('cslnb')
            return

    two = []
    for a, c in cnts.items():
        if c == 2:
            two.append(a)
            
    if len(two) > 1:        
        print('cslnb')
        return

    if len(two) == 1:
        if two[0] == 0 or two[0] - 1 in cnts:
            print('cslnb')
            return

    ans = A[0]
    A[0] = 0
    for i in range(1, n):
        ans += A[i] - i
        A[i] = i

    print('sjfnb' if ans % 2 else 'cslnb')
    
    return

solve()