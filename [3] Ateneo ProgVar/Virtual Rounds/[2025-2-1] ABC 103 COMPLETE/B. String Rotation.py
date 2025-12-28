def solve():
    S, T = input(), input()
    
    if S == T:
        print("Yes")
        return
    
    n = len(S)
    for i in range(1, n):
        if S[i:] + S[:i] == T:
            print("Yes")
            return
        
    print("No")
        
    return

solve()