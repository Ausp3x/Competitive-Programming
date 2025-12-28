import random
from os import system

class Color():
    r = '\033[31m'
    g = '\033[32m'
    reset = '\033[0m'

N = 1000
optim_name = 'optim'
brute_name = 'brute'

def generator(t):
    return 

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