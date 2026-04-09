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
    int n;
    cin >> n;
    string s(n + 1, 'X');
    for (int i = 1; i <= n; i++)
        cin >> s[i];

    vector<lng> P(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        P[i] += P[i - 1];
        if (s[i] == '(') 
            P[i]++;
        else
            P[i]--;
    }

    int l = 1;
    vector<mint> dp(n + 1), dpc_prf(n + 1), dpa_prf(n + 1);
    for (int i = 1; i <= n; i++) {
        dp[i] = 1 + dpc_prf[i - 1] + dpa_prf[i - 1] - dpa_prf[l - 1];
        
        dpc_prf[i] = dpc_prf[i - 1];
        dpa_prf[i] = dpa_prf[i - 1];
        if (s[i] == ')') {
            dpc_prf[i] += dp[i];
        } else {
            dpa_prf[i] += dp[i];
        }

        if (P[i] < 2)
            l = i + 1;
    }

    mint ans = 0;
    for (int i = 1; i <= n; i++)
        ans += (s[i] == ')' ? dp[i] : mint(2).pow(i - 1));
        
    cout << ans << endl;

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