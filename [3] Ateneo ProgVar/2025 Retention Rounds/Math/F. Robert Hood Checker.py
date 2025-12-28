from os import system
from random import *

class Color():
    r = '\033[31m'
    g = '\033[32m'
    reset = '\033[0m'

N = 1000
optim_name = 'roberthood'
brute_name = 'roberthood_brute'

def generator(t):
    n = randint(1, 1000)
    
    inp = f'{n}\n'
    for i in range(n):
        inp += f'{randint(-1000, 1000)} {randint(-1000, 1000)}\n'
    
    return inp

system(f'g++ -o "{optim_name}" "{optim_name}.cpp"')
system(f'g++ -o "{brute_name}" "{brute_name}.cpp"')

for i in range(N):
    with open('inp.txt', 'w+') as f:
        f.write(str(generator(100)))
    
    system(f'"{optim_name}.exe" < inp.txt > out-optim.txt')
    system(f'"{brute_name}.exe" < inp.txt > out-brute.txt')
    # system(f'python "{brute_name}.py" < inp.txt > out-brute.txt')

    with open('out-optim.txt', 'r+') as f1, open('out-brute.txt', 'r+') as f2:
        if (f1.read() != f2.read()):
            print(f'{Color.r}FAIL {i}{Color.reset}') 
            exit(1)
            
    print(f'{Color.g}PASS {i}{Color.reset}')