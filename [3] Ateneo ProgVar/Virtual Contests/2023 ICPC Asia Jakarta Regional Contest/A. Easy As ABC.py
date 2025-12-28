def isValidMove(x, y):
    return (abs(y[0] - x[0]) <= 1) and (abs(y[1] - x[1]) <= 1) and (abs(y[0] - x[0]) + abs(y[1] - x[1]) > 0)    

def solve():
    N = 3
    grid = [input() for _ in range(N)]

    choices = []
    for i in range(N):
        for j in range(N):
            choices.append([i, j])
            
    S = set()
    for x in choices:
        for y in choices:
            for z in choices:
                if x == y or x == z or y == z:
                    continue
                
                if not isValidMove(x, y) or not isValidMove(y, z):
                    continue
                
                S.add(grid[x[0]][x[1]] + grid[y[0]][y[1]] + grid[z[0]][z[1]])
    
    S_list = list(S)
    S_list.sort()
    
    print(S_list[0])
    return

solve()