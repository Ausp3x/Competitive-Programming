def solve():
    s = input()
    
    print('Yes' if s == s[0].upper() + s[1:].lower() else 'No')
    
    return

solve()