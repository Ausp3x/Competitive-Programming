alls = [
    "There is a knight among us.",
    "There is a knave among us.",
    "There are more knights than knaves.",
    "There are more knaves than knights.",
    "All of us are the same.",
    "Those other two are the same, and different from me.",
    "I am different from one of those two, but the same as the other one.",
    "Both of those two would say I am a knight.",
    "Both of those two would say I am a knave.",
    "If asked what I am, those two would give different answers."
]

# 0 - liar, 1 - honest
def checkTruth(idx, state, pos: list) -> bool:
    global alls
    
    I = [i for i in [0, 1, 2] if i != idx]
    pos_red = [pos[I[i]] for i in range(2)]
    if state == alls[0]:
        return ((1 in pos) ^ (pos[idx] == 0))
    elif state == alls[1]:
        return ((0 in pos) ^ (pos[idx] == 0))
    elif state == alls[2]:
        return ((sum(pos) >= 2) ^ (pos[idx] == 0))
    elif state == alls[3]:
        return ((sum(pos) < 2) ^ (pos[idx] == 0))
    elif state == alls[4]:
        return ((sum(pos) == 3 or sum(pos) == 0) ^ (pos[idx] == 0))
    elif state == alls[5]:
        return ((pos_red[0] == pos_red[1] and pos_red[0] != pos[idx]) ^ (pos[idx] == 0))
    elif state == alls[6]:
        return ((pos_red[0] != pos_red[1]) ^ (pos[idx] == 0))
    elif state == alls[7]:
        return ((sum(pos) == 3 or sum(pos) == 0) ^ (pos[idx] == 0))
    elif state == alls[8]:
        return ((pos_red[0] == pos_red[1] and pos_red[0] != pos[idx]) ^ (pos[idx] == 0))
    elif state == alls[9]:
        return ((pos_red[0] != pos_red[1]) ^ (pos[idx] == 0))

def solve():
    cur = [input() for _ in range(3)]
    
    valid = [0 for _ in range(3)]
    for i in range(1 << 3):
        pos = []
        for j in range(3):
            pos.append(1 if i & (1 << j) else 0)
        pos.reverse()
        
        is_good = True
        for j in range(3):
            is_good &= checkTruth(j, cur[j], pos)
            
        if is_good:
            for j in range(3):
                valid[j] |= 1 << pos[j]

    if sum(valid) == 0:
        print("narrator: liar!")
        return

    people = ["Alice:", "Bob:", "Cindy:"]
    for i in range(3):
        if valid[i] == 1:
            print(people[i], "knave")
        elif valid[i] == 2:
            print(people[i], "knight")
        elif valid[i] == 3:
            print(people[i], "uncertain")
        
    return

t = int(input())
for _ in range(t):
    solve()
    print("---------------")
    useless = input()