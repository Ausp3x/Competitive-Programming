// 人外有人，天外有天
// author: Ausp3x
// g++ -Wall -Wextra -o <name> <name>.cpp
// <name>.exe < in > out

#pragma GCC optimize("O3, fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
// #define DEBUG
using lng = long long;
using lll = __int128;
template<typename T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> // lower_bound and upper_bound are broken
using indexed_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

struct ModInt {
    lng val;
    static lng MOD;

    ModInt(lng x = 0) {
        val = x % MOD;
        if (val < 0) { 
            val += MOD;
        }
    }

    ModInt(const ModInt &other) : val(other.val) {}
    
    static void setMod(lng mod) {
        assert(1 <= mod);
        MOD = mod;
    }
    
    ModInt &operator++() {
        val++;
        if (val == MOD) {
            val = 0;
        }
        
        return *this;
    }

    ModInt &operator--() {
        if (val == 0) {
            val = MOD;
        }
        val--;
        
        return *this;
    }

    ModInt operator++(int) {
        ModInt res = *this;
        ++*this;
        
        return res;
    }

    ModInt operator--(int) {
        ModInt res = *this;
        --*this;

        return res;
    }

    ModInt &operator=(const ModInt &other) {
        val = other.val;
        
        return *this;
    }

    ModInt &operator+=(const ModInt &other) {
        val += other.val;
        if (val >= MOD) {
            val -= MOD;
        }

        return *this;
    }
    
    ModInt &operator-=(const ModInt &other) {
        val -= other.val;
        if (val < 0) {
            val += MOD;
        }

        return *this;
    }
    
    ModInt &operator*=(const ModInt &other) {
        val = lll(1) * val * other.val % MOD;

        return *this;
    }
    
    ModInt inv() const {
        if (val != 0) {
            assert(gcd(val, MOD) == 1);
        }

        lll x = val, y = MOD, a = 1, b = 0, t;
        while (y > 0) {
            t = x / y;
            x -= t * y;
            a -= t * b;
            swap(x, y);
            swap(a, b);
        }

        return ModInt(a);
    }
    
    ModInt &operator/=(const ModInt &other) {
        val = lll(1) * val * other.inv().val % MOD;

        return *this;
    }

    ModInt pow(lng exp) const {
        assert(0 <= exp);
        ModInt bse = *this, res = 1;
        while (exp > 0) {
            if (exp & 1) {
                res *= bse;
            }
            
            bse *= bse;
            exp >>= 1;
        }

        return res;
    }

    ModInt operator+() const {
        return *this;
    }
    
    ModInt operator-() const {
        return ModInt() - *this;
    }

    friend ModInt operator+(const ModInt &x, const ModInt &y) {
        return ModInt(x) += y;
    }
    
    friend ModInt operator-(const ModInt &x, const ModInt &y) {
        return ModInt(x) -= y;
    }

    friend ModInt operator*(const ModInt &x, const ModInt &y) {
        return ModInt(x) *= y;
    }
    
    friend ModInt operator/(const ModInt &x, const ModInt &y) {
        return ModInt(x) /= y;
    }

    friend bool operator==(const ModInt &x, const ModInt &y) {
        return x.val == y.val;
    }

    friend bool operator!=(const ModInt &x, const ModInt &y) {
        return x.val != y.val;
    }

    friend istream &operator>>(istream &is, ModInt &x) {
        lng y;
        is >> y;
        x = ModInt(y);

        return is;
    }

    friend ostream &operator<<(ostream &os, const ModInt &x) {
        return os << x.val;
    }
};
lng ModInt::MOD = 998'244'353;

void solve() {
    lng n;
    cin >> n;

    auto matMul = [&](vector<vector<ModInt>> &A, vector<vector<ModInt>> &B) -> vector<vector<ModInt>> {
        int rowA = A.size();
        if (rowA == 0) 
            return {};
        int colA = A[0].size();
        
        int rowB = B.size();
        assert(rowB != 0 && colA == rowB);

        int colB = B[0].size();
        vector<vector<ModInt>> C(rowA, std::vector<ModInt>(colB, 0));
        for (int i = 0; i < rowA; i++) {
            for (int j = 0; j < colB; j++) {
                for (int k = 0; k < colA; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        return C;
    };

    vector<vector<ModInt>> A = {{0, 0, 0, 0, 1, 0, 0, 0}};
    vector<vector<ModInt>> M = {
        {1, 1, 1, 2, 0, 0, 0, 0},
        {1, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 3, 3, 6, 1, 1, 1, 2},
        {0, 0, 0, 3, 1, 0, 0, 1},
        {0, 0, 0, 3, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 0, 0}
    };
    
    lng exp = n - 1;
    vector<vector<ModInt>> N = {
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1}
    };
    while (exp > 0) {
        if (exp & 1) {
            N = matMul(N, M);
        }
        
        M = matMul(M, M);
        exp >>= 1;
    }

    A = matMul(A, N);

    ModInt ans = 0;
    for (int i = 0; i < 4; i++)
        ans += A[0][i];

    cout << ans << endl;

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}