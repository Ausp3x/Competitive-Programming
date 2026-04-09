import random
import math
import subprocess
import sys

# Inf flags
INF = "inf"
NINF = "-inf"

def is_inf(val):
    return val in (INF, NINF)

def get_sgn(val):
    if is_inf(val): return -1 if val == NINF else 1
    return -1 if val < 0 else 1

# C++ Division truncates towards zero. Python truncates towards -inf.
def cpp_div(a, b):
    res = abs(a) // abs(b)
    return -res if (a < 0) ^ (b < 0) else res

def cpp_mod(a, b):
    return a - cpp_div(a, b) * b

# Extended GCD replicating InfInt logic exactly
def exgcd(a, b):
    if is_inf(a): return b, 0, 1
    if is_inf(b): return a, 1, 0
    x0, y0, x1, y1 = 1, 0, 0, 1
    while b != 0:
        q = cpp_div(a, b)
        r = cpp_mod(a, b)
        a, b = b, r
        x0, x1 = x1, x0 - q * x1
        y0, y1 = y1, y0 - q * y1
    return a, x0, y0

class Oracle:
    @staticmethod
    def add(a, b):
        if is_inf(a) and is_inf(b): return 0 if a != b else a
        if is_inf(a): return a
        if is_inf(b): return b
        return a + b

    @staticmethod
    def sub(a, b):
        if is_inf(b): b = INF if b == NINF else NINF
        else: b = -b
        return Oracle.add(a, b)

    @staticmethod
    def mul(a, b):
        if a == 0 or b == 0: return 0
        if is_inf(a) or is_inf(b):
            return INF if get_sgn(a) * get_sgn(b) == 1 else NINF
        return a * b

    @staticmethod
    def div(a, b):
        if is_inf(a) and is_inf(b): return get_sgn(a) * get_sgn(b)
        if is_inf(b): return 0
        if is_inf(a): return INF if get_sgn(a) * get_sgn(b) == 1 else NINF
        return cpp_div(a, b)

    @staticmethod
    def mod(a, b):
        if is_inf(a): return 0
        if is_inf(b): return a
        return cpp_mod(a, b)
        
    @staticmethod
    def power(a, b): 
        if is_inf(a):
            if b == 0: return 1
            if b % 2 == 0: return INF
            return a
        return a ** b

    @staticmethod
    def inv(a, mod):
        if is_inf(a) or is_inf(mod): return -1
        a = cpp_mod(a, mod)
        a = cpp_mod(a + mod, mod)
        if a == 0: return -1
        g, x, y = exgcd(a, mod)
        if g != 1: return -1
        x = cpp_mod(x, mod)
        x = cpp_mod(x + mod, mod)
        return x

    @staticmethod
    def ctz(val):
        if val == 0: return 0
        val = abs(val)
        return (val & -val).bit_length() - 1

    @staticmethod
    def popcnt(val):
        return bin(abs(val)).count('1')

    @staticmethod
    def bin_str(val):
        if val == 0: return "0"
        s = bin(abs(val))[2:]
        return "-" + s if val < 0 else s


def generate_operand(allow_inf=True, max_digits=1000, force_pos=False):
    if allow_inf and random.random() < 0.05:
        return INF if force_pos or random.random() < 0.5 else NINF
    val = random.randint(0, 10**max_digits)
    if not force_pos and random.random() < 0.5: val = -val
    return val

def run_tests():
    print("Compiling test_iint.cpp...")
    compile_cmd = ["g++", "-O3", "-std=c++17", "test_iint.cpp", "-o", "test_iint"]
    if subprocess.run(compile_cmd).returncode != 0:
        print("Compilation failed!")
        sys.exit(1)
        
    process = subprocess.Popen(["./test_iint"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    
    ops = [
        "add", "sub", "mul", "div", "mod", "pow", "sqrt", 
        "shl", "shr", "and", "or", "xor", "exgcd", "inv",
        "bin", "ctz", "popcnt"
    ]
    
    # Operations that ONLY take one argument
    unary_ops = ["sqrt", "bin", "ctz", "popcnt"]

    # Operations where the C++ implementation explicitly asserts `!is_inf`
    ban_inf_ops = ["and", "or", "xor", "bin", "ctz", "popcnt"]
    
    test_cases = 10000
    print(f"Running {test_cases} randomized stress tests...\n")
    
    for i in range(test_cases):
        op = random.choice(ops)
        
        allow_inf = op not in ban_inf_ops
        max_dig = 3000 if op in ["add", "sub", "mul"] else 600
        
        a = generate_operand(allow_inf=allow_inf, max_digits=max_dig, force_pos=(op=="sqrt"))
        b = generate_operand(allow_inf=allow_inf, max_digits=max_dig)
        
        # Division by zero guards
        if op in ["div", "mod", "inv", "exgcd"] and b == 0: b = 1
        
        # Shifting/Pow limits to prevent TLE
        if op in ["pow", "shl", "shr"]:
            b = random.randint(0, 1800)
            
        expected = ""
        try:
            if op == "add": expected = str(Oracle.add(a, b))
            elif op == "sub": expected = str(Oracle.sub(a, b))
            elif op == "mul": expected = str(Oracle.mul(a, b))
            elif op == "div": expected = str(Oracle.div(a, b))
            elif op == "mod": expected = str(Oracle.mod(a, b))
            elif op == "pow": expected = str(Oracle.power(a, b))
            elif op == "sqrt": expected = str(INF if is_inf(a) else math.isqrt(a))
            elif op == "shl": expected = str(a << b) if not is_inf(a) else str(a)
            elif op == "shr": expected = str(a >> b) if not is_inf(a) else str(a)
            elif op == "and": expected = str(a & b)
            elif op == "or":  expected = str(a | b)
            elif op == "xor": expected = str(a ^ b)
            elif op == "inv": expected = str(Oracle.inv(a, b))
            elif op == "bin": expected = Oracle.bin_str(a)
            elif op == "ctz": expected = str(Oracle.ctz(a))
            elif op == "popcnt": expected = str(Oracle.popcnt(a))
            elif op == "exgcd": 
                g, x, y = exgcd(a, b)
                expected = f"{g} {x} {y}"
                
        except Exception as e:
            continue
            
        # Feed to C++
        query = f"{op} {a}" + ("\n" if op in unary_ops else f" {b}\n")
        process.stdin.write(query)
        process.stdin.flush()
        
        # Get C++ Output
        cpp_out = process.stdout.readline().strip()
        
        if cpp_out != expected:
            print(f"\n[FAIL] Test {i + 1} failed!")
            print(f"Operation: {op} {a} {'' if op in unary_ops else b}")
            print(f"Expected : {expected}")
            print(f"Got      : {cpp_out}")
            process.kill()
            sys.exit(1)
            
        # Live Progress Update
        if (i + 1) % 100 == 0 or (i + 1) == test_cases:
            print(f"\rCompleted {i + 1} / {test_cases} tests...", end="", flush=True)
            
    print("\n\nAll tests passed! Your InfInt template is flawless.")
    process.terminate()

if __name__ == "__main__":
    run_tests()