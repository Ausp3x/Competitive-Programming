def solve():
    b = int(input())
    w = int(input())
    p = int(input())
    n = int(input())
    
    if b >= w:
        print("Watermelon")
        return

    if b >= p:
        print("Pomegranates")
        return
    
    if b >= n:
        print("Nuts")
        return
    
    print("Nothing")
    return
    
solve()