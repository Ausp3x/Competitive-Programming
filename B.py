def solve():
    a_x, a_y, b_x, b_y, c_x, c_y = map(int, input().split())
    
    ab = (b_x - a_x) ** 2 + (b_y - a_y) ** 2
    bc = (c_x - b_x) ** 2 + (c_y - b_y) ** 2
    
    cross = (b_x - a_x) * (c_y - b_y) - (b_y - a_y) * (c_x - b_x)

    print('Yes' if ab == bc and cross != 0 else 'No')

    return

solve()