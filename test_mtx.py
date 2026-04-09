import random
import subprocess
import sys

MOD = 998244353

def minv(a):
    return pow(a, MOD - 2, MOD)

class ModMatrix:
    @staticmethod
    def madd(A, B):
        return [[(A[i][j] + B[i][j]) % MOD for j in range(len(A[0]))] for i in range(len(A))]

    @staticmethod
    def msub(A, B):
        return [[(A[i][j] - B[i][j]) % MOD for j in range(len(A[0]))] for i in range(len(A))]

    @staticmethod
    def mmul(A, B):
        R = [[0]*len(B[0]) for _ in range(len(A))]
        for i in range(len(A)):
            for k in range(len(B)):
                if A[i][k] == 0: continue
                for j in range(len(B[0])):
                    R[i][j] = (R[i][j] + A[i][k] * B[k][j]) % MOD
        return R

    @staticmethod
    def mpow(A, b):
        n = len(A)
        R = [[1 if i == j else 0 for j in range(n)] for i in range(n)]
        base = [row[:] for row in A]
        while b > 0:
            if b & 1: R = ModMatrix.mmul(R, base)
            base = ModMatrix.mmul(base, base)
            b >>= 1
        return R

    @staticmethod
    def mdet(A):
        n = len(A)
        mat = [row[:] for row in A]
        res = 1
        for i in range(n):
            piv = i
            while piv < n and mat[piv][i] == 0: piv += 1
            if piv == n: return 0
            if i != piv:
                mat[i], mat[piv] = mat[piv], mat[i]
                res = (MOD - res) % MOD
            res = (res * mat[i][i]) % MOD
            d = minv(mat[i][i])
            for j in range(i, n): mat[i][j] = (mat[i][j] * d) % MOD
            for k in range(i + 1, n):
                aki = mat[k][i]
                if aki == 0: continue
                for j in range(i, n): mat[k][j] = (mat[k][j] - mat[i][j] * aki) % MOD
        return res

    @staticmethod
    def minv_mat(A):
        n = len(A)
        mat = [row[:] for row in A]
        res = [[1 if i == j else 0 for j in range(n)] for i in range(n)]
        for i in range(n):
            piv = i
            while piv < n and mat[piv][i] == 0: piv += 1
            if piv == n: return None
            if i != piv:
                mat[i], mat[piv] = mat[piv], mat[i]
                res[i], res[piv] = res[piv], res[i]
            d = minv(mat[i][i])
            for j in range(i, n): mat[i][j] = (mat[i][j] * d) % MOD
            for j in range(n): res[i][j] = (res[i][j] * d) % MOD
            for k in range(n):
                if k == i: continue
                aki = mat[k][i]
                if aki == 0: continue
                for j in range(i, n): mat[k][j] = (mat[k][j] - mat[i][j] * aki) % MOD
                for j in range(n): res[k][j] = (res[k][j] - res[i][j] * aki) % MOD
        return res

    @staticmethod
    def mref(A):
        n, m = len(A), len(A[0])
        mat = [row[:] for row in A]
        r = 0
        for c in range(m):
            if r >= n: break
            piv = r
            while piv < n and mat[piv][c] == 0: piv += 1
            if piv == n: continue
            if r != piv: mat[r], mat[piv] = mat[piv], mat[r]
            d = minv(mat[r][c])
            for j in range(c, m): mat[r][j] = (mat[r][j] * d) % MOD
            for i in range(r + 1, n):
                aic = mat[i][c]
                if aic == 0: continue
                for j in range(c, m): mat[i][j] = (mat[i][j] - mat[r][j] * aic) % MOD
            r += 1
        return mat

    @staticmethod
    def mrref(A):
        n, m = len(A), len(A[0])
        mat = [row[:] for row in A]
        r = 0
        for c in range(m):
            if r >= n: break
            piv = r
            while piv < n and mat[piv][c] == 0: piv += 1
            if piv == n: continue
            if r != piv: mat[r], mat[piv] = mat[piv], mat[r]
            d = minv(mat[r][c])
            for j in range(c, m): mat[r][j] = (mat[r][j] * d) % MOD
            for i in range(n):
                if i == r: continue
                aic = mat[i][c]
                if aic == 0: continue
                for j in range(c, m): mat[i][j] = (mat[i][j] - mat[r][j] * aic) % MOD
            r += 1
        return mat

    @staticmethod
    def mtrp(A):
        return [[A[j][i] for j in range(len(A))] for i in range(len(A[0]))]

    @staticmethod
    def mtrace(A):
        return sum(A[i][i] for i in range(len(A))) % MOD

    @staticmethod
    def mcross(A, B, axis):
        def get(mat, i): return mat[0][i] if len(mat) == 1 else mat[i][0]
        x = (get(A, 1) * get(B, 2) - get(A, 2) * get(B, 1)) % MOD
        y = (get(A, 2) * get(B, 0) - get(A, 0) * get(B, 2)) % MOD
        z = (get(A, 0) * get(B, 1) - get(A, 1) * get(B, 0)) % MOD
        return [[x, y, z]] if axis == 0 else [[x], [y], [z]]

    @staticmethod
    def mdot(A, B):
        def get(mat, i): return mat[0][i] if len(mat) == 1 else mat[i][0]
        length = max(len(A), len(A[0]))
        return sum(get(A, i) * get(B, i) for i in range(length)) % MOD

    @staticmethod
    def mconcat(A, B, axis):
        if axis == 0: return [A[i] + B[i] for i in range(len(A))]
        else: return A + B

def format_mat(mat):
    if isinstance(mat, list):
        if len(mat) == 0: return ""
        if isinstance(mat[0], list):
            # Formatted to perfectly match your C++ trailing spaces
            return "\n".join(" ".join(map(str, row)) + " " for row in mat)
    return str(mat)

def rand_mat(n, m):
    return [[random.randint(0, MOD - 1) for _ in range(m)] for _ in range(n)]

def run_tests():
    print("Compiling test_mtx.cpp...")
    compile_cmd = ["g++", "-O3", "-std=c++17", "test_mtx.cpp", "-o", "test_mtx"]
    if subprocess.run(compile_cmd).returncode != 0:
        print("Compilation failed!")
        sys.exit(1)
        
    process = subprocess.Popen(["./test_mtx"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    
    ops = ["add", "sub", "mul", "pow", "det", "inv", "ref", "rref", "trace", "trp", "cross", "dot", "concat"]
    test_cases = 10000
    print(f"Running {test_cases} randomized Matrix stress tests...\n")
    
    for i in range(test_cases):
        op = random.choice(ops)
        
        # Build constraints
        sz = 12 # Keep bounds reasonable for fast local execution
        n1, m1 = random.randint(1, sz), random.randint(1, sz)
        n2, m2 = random.randint(1, sz), random.randint(1, sz)
        
        query = f"{op} "
        expected = None
        
        if op in ["add", "sub"]:
            A = rand_mat(n1, m1)
            B = rand_mat(n1, m1)
            query += f"{n1} {m1} {n1} {m1}\n" + format_mat(A) + "\n" + format_mat(B) + "\n"
            expected = format_mat(ModMatrix.madd(A, B) if op == "add" else ModMatrix.msub(A, B))
            
        elif op == "mul":
            A = rand_mat(n1, m1)
            B = rand_mat(m1, m2)
            query += f"{n1} {m1} {m1} {m2}\n" + format_mat(A) + "\n" + format_mat(B) + "\n"
            expected = format_mat(ModMatrix.mmul(A, B))
            
        elif op == "pow":
            A = rand_mat(n1, n1)
            exp = random.randint(0, 1000000)
            query += f"{n1} {exp}\n" + format_mat(A) + "\n"
            expected = format_mat(ModMatrix.mpow(A, exp))
            
        elif op in ["det", "trace"]:
            A = rand_mat(n1, n1)
            query += f"{n1}\n" + format_mat(A) + "\n"
            expected = str(ModMatrix.mdet(A) if op == "det" else ModMatrix.mtrace(A))
            
        elif op in ["inv", "ref", "rref", "trp"]:
            if op == "inv": m1 = n1 # Must be square
            A = rand_mat(n1, m1)
            
            if op == "inv":
                expected_mat = ModMatrix.minv_mat(A)
                while expected_mat is None: # Loop until matrix is not strictly singular
                    A = rand_mat(n1, n1)
                    expected_mat = ModMatrix.minv_mat(A)
                expected = format_mat(expected_mat)
            elif op == "ref": expected = format_mat(ModMatrix.mref(A))
            elif op == "rref": expected = format_mat(ModMatrix.mrref(A))
            elif op == "trp": expected = format_mat(ModMatrix.mtrp(A))
                
            query += f"{n1} {m1}\n" + format_mat(A) + "\n"
            
        elif op == "cross":
            rA, cA = (1, 3) if random.randint(0, 1) == 0 else (3, 1)
            rB, cB = (1, 3) if random.randint(0, 1) == 0 else (3, 1)
            axis = random.randint(0, 1)
            A = rand_mat(rA, cA)
            B = rand_mat(rB, cB)
            query += f"{rA} {cA} {rB} {cB} {axis}\n" + format_mat(A) + "\n" + format_mat(B) + "\n"
            expected = format_mat(ModMatrix.mcross(A, B, axis))
            
        elif op == "dot":
            l = random.randint(1, sz)
            rA, cA = (1, l) if random.randint(0, 1) == 0 else (l, 1)
            rB, cB = (1, l) if random.randint(0, 1) == 0 else (l, 1)
            A = rand_mat(rA, cA)
            B = rand_mat(rB, cB)
            query += f"{rA} {cA} {rB} {cB}\n" + format_mat(A) + "\n" + format_mat(B) + "\n"
            expected = str(ModMatrix.mdot(A, B))
            
        elif op == "concat":
            axis = random.randint(0, 1)
            if axis == 0: B = rand_mat(n1, m2) # Same rows
            else: B = rand_mat(n2, m1) # Same cols
            A = rand_mat(n1, m1)
            
            query += f"{axis} {len(A)} {len(A[0])} {len(B)} {len(B[0])}\n" + format_mat(A) + "\n" + format_mat(B) + "\n"
            expected = format_mat(ModMatrix.mconcat(A, B, axis))

        # Send to C++
        process.stdin.write(query)
        process.stdin.flush()
        
        # Read matching lines (strip standardizes formatting between Python/C++ trailing spaces)
        cpp_out = []
        lines_to_read = 1
        if "\n" in expected: lines_to_read = expected.count("\n") + 1
        
        for _ in range(lines_to_read):
            cpp_out.append(process.stdout.readline().strip())
        cpp_out = "\n".join(cpp_out)
        
        # Clean expected string for robust comparison against parsed C++ string
        expected = "\n".join(line.strip() for line in expected.split("\n"))
        
        if cpp_out != expected:
            print(f"\n[FAIL] Test {i + 1} failed on {op}!")
            print(f"Expected:\n{expected}")
            print(f"Got:\n{cpp_out}")
            process.kill()
            sys.exit(1)
            
        if (i + 1) % 100 == 0 or (i + 1) == test_cases:
            print(f"\rCompleted {i + 1} / {test_cases} tests...", end="", flush=True)

    print("\n\nAll tests passed! Your Matrix template is flawless.")
    process.terminate()

if __name__ == "__main__":
    run_tests()