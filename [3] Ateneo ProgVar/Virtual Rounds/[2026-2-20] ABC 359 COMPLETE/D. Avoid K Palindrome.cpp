// 人外有人，天外有天
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
using lng = long long;
using lll = __int128;
template<typename T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
using mint = ModInt<998'244'353>;

void solve() {
    int n, k;
    cin >> n >> k;
    string s = "X";
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;

        s += c; 
    }

    auto isPalin = [&](int a) -> bool {
        for (int i = 0; i < k / 2; i++) 
            if ((a & (1 << i)) > 0 != (a & (1 << (k - i - 1))) > 0)
                return false;

        return true;
    };

    int N = 1 << k;
    vector<bool> palin(N);
    for (int i = 0; i < N; i++)
        palin[i] = isPalin(i);
        
    vector memo(n + 1, vector<mint>(N));
    memo[0][0] = 1;
    for (int i = 0; i < n; i++) {
        if (i < k - 1) {
            for (int j = 0; j < N; j++) {
                if (s[i + 1] == 'A' || s[i + 1] == '?') {
                    int j_nxt = 2 * j % N;
                    memo[i + 1][j_nxt] += memo[i][j];
                }
                
                if (s[i + 1] == 'B' || s[i + 1] == '?') {
                    int j_nxt = (2 * j + 1) % N;
                    memo[i + 1][j_nxt] += memo[i][j];
                }
            }

            // mint cur = 0;
            // for (int j = 0; j < N; j++)
            //     cur += memo[i + 1][j];
            // cout << i + 1 << ": " << cur << endl;

            continue;
        }

        for (int j = 0; j < N; j++) {
            if (s[i + 1] == 'A' || s[i + 1] == '?') {
                int j_nxt = 2 * j % N;
                if (!palin[j_nxt])
                    memo[i + 1][j_nxt] += memo[i][j];
            }
            
            if (s[i + 1] == 'B' || s[i + 1] == '?') {
                int j_nxt = (2 * j + 1) % N;
                if (!palin[j_nxt])
                    memo[i + 1][j_nxt] += memo[i][j];
            }
        }

        // mint cur = 0;
        // for (int j = 0; j < N; j++)
        //     cur += memo[i + 1][j];
        // cout << i + 1 << ": " << cur << endl;
    }

    mint ans = 0;
    for (int j = 0; j < N; j++)
        ans += memo[n][j];

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