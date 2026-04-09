for i in range(64):
    for j in range(64):
        if i | j == i:
            print(1, end=' ')
        else:
            print(0, end=' ')
    print()