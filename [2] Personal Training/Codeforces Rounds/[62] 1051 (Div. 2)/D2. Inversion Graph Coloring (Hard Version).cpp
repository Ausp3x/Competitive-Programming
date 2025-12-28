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

template<lng MOD>
struct ModInt {
    lng val;

    ModInt(lng x = 0) : val(x % MOD) {
        if (val < 0) { 
            val += MOD;
        }
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
        val = val * other.val % MOD;

        return *this;
    }
    
    ModInt inv() const {
        assert(val != 0);

        lng x = val, y = MOD, a = 1, b = 0, t;
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
        val = val * other.inv().val % MOD;

        return *this;
    }

    ModInt pow(lng exp) const {
        assert(exp >= 0);
        
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
using mint = ModInt<1'000'000'007>;

struct FenTree {
    int D, X, Y, Z;
    vector<mint> B1, B2, bit;
    
    FenTree(int x, int y): D(2), X(x), Y(y), bit((X + 1) * (Y + 1)) {
        assert(x > 0 && y > 0);
    }

    template <typename T>
    FenTree(int x, int y, const vector<vector<T>> &arr): FenTree(x, y) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                pointAddUpdate(i + 1, j + 1, arr[i][j]);
            }
        }
    }

    // 2D methods
    inline int getIdx(int i, int j) const {
        assert(D == 2);

        return i * (Y + 1) + j;
    }

    void pointAddUpdate(int i_cur, int j_cur, mint del) {
        assert(D == 2);
        for (int i = i_cur; i <= X; i += i & -i) {
            for (int j = j_cur; j <= Y; j += j & -j) {
                bit[getIdx(i, j)] += del;
            }
        }
    }

    mint prefixSumQuery(int i_cur, int j_cur) const {
        assert(D == 2);
        mint sum = 0;
        for (int i = i_cur; i > 0; i -= i & -i) {
            for (int j = j_cur; j > 0; j -= j & -j) {
                sum += bit[getIdx(i, j)];
            }
        }
        
        return sum;
    }

    mint rangeSumQuery(int x1, int y1, int x2, int y2) const {
        assert(D == 2);
        if (x1 > x2 || y1 > y2) {
            return 0;
        }
        
        return prefixSumQuery(x2, y2)
             - prefixSumQuery(x1 - 1, y2) - prefixSumQuery(x2, y1 - 1)
             + prefixSumQuery(x1 - 1, y1 - 1);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> A(n);
    for (int &a : A)
        cin >> a;

    FenTree dp(n + 1, n + 1);
    dp.pointAddUpdate(A[0] + 1, 1, 1);
    for (int i = 1; i < n; i++) {
        vector<mint> B(A[i] + 1);
        for (int k = 0; k <= A[i]; k++)
            B[k] += dp.rangeSumQuery(1, k + 1, A[i] + 1, k + 1);

        vector<mint> C(n + 1);
        for (int j = A[i] + 1; j <= n; j++)
            C[j] += dp.rangeSumQuery(j + 1, 1, j + 1, A[i] + 1);

        dp.pointAddUpdate(A[i] + 1, 1, 1);
        for (int k = 0; k <= A[i]; k++)
            dp.pointAddUpdate(A[i] + 1, k + 1, B[k]);
        for (int j = A[i] + 1; j <= n; j++)
            dp.pointAddUpdate(j + 1, A[i] + 1, C[j]);
    }

    cout << dp.rangeSumQuery(1, 1, n + 1, n + 1) + 1 << endl;

    return;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}