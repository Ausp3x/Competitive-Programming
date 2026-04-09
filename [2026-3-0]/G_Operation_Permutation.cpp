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
    lng n;

    ModInt(lng N = 0): n(N % MOD) {
        if (n < 0) { 
            n += MOD;}
    }
    
    ModInt &operator++() {
        n++;
        if (n == MOD) {
            n = 0;}
        
        return *this;
    }

    ModInt &operator--() {
        if (n == 0) {
            n = MOD;}
        n--;
        
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
        n += other.n;
        if (n >= MOD) {
            n -= MOD;}

        return *this;
    }
    
    ModInt &operator-=(const ModInt &other) {
        n -= other.n;
        if (n < 0) {
            n += MOD;}

        return *this;
    }
    
    ModInt &operator*=(const ModInt &other) {
        n = n * other.n % MOD;

        return *this;
    }

    ModInt &operator/=(const ModInt &other) {
        n = n * other.inv().n % MOD;

        return *this;
    }

    ModInt operator+() const {
        return *this;
    }
    
    ModInt operator-() const {
        return ModInt() - *this;
    }

    friend ModInt operator+(const ModInt &a, const ModInt &b) {
        return ModInt(a) += b;
    }
    
    friend ModInt operator-(const ModInt &a, const ModInt &b) {
        return ModInt(a) -= b;
    }

    friend ModInt operator*(const ModInt &a, const ModInt &b) {
        return ModInt(a) *= b;
    }
    
    friend ModInt operator/(const ModInt &a, const ModInt &b) {
        return ModInt(a) /= b;
    }

    friend bool operator==(const ModInt &a, const ModInt &b) {
        return a.n == b.n;
    }

    friend bool operator!=(const ModInt &a, const ModInt &b) {
        return a.n != b.n;
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        lng b;
        is >> b;
        a = ModInt(b);

        return is;
    }

    friend ostream &operator<<(ostream &os, const ModInt &a) {
        return os << a.n;
    }

    ModInt inv() const {
        assert(n != 0);

        lng a = n, b = MOD, x = 1, y = 0;
        while (b > 0) {
            lng q = a / b;
            a = exchange(b, a - q * b);
            x = exchange(y, x - q * y);
        }

        return ModInt(x);
    }

    ModInt pow(lng b) const {
        assert(b >= 0);
        
        ModInt a = *this;
        ModInt res = 1;
        while (b > 0) {
            if (b & 1) {
                res *= a;}
            
            a *= a;
            b >>= 1;
        }

        return res;
    }
};
using mint = ModInt<1'000'000'007>;

struct ModFac {
    int n;
    vector<mint> fac, inv_fac;

    ModFac(int n): n(n) {
        fac.resize(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i;
        }

        inv_fac.resize(n + 1);
        inv_fac[n] = fac[n].inv();
        for (int i = n - 1; i >= 0; i--) {
            inv_fac[i] = inv_fac[i + 1] * (i + 1);
        }
    }

    mint combiNR(int x, int y) const {
        if (y > x || y < 0) {
            return mint(0);
        }

        assert(x <= n);

        return fac[x] * inv_fac[y] * inv_fac[x - y];
    }

    mint combiWR(int x, int y) const {
        if (x < 1 || y < 0) {
            return mint(0);
        }

        assert(x + y - 1 <= n);

        return fac[x + y - 1] * inv_fac[y] * inv_fac[x - 1];
    }

    mint permuNR(int x, int y) const {
        if (y > x || y < 0) {
            return mint(0);
        }

        assert(x <= n);   

        return fac[x] * inv_fac[x - y];
    }

    mint permuWR(int x, int y) const {
        if (y < 0) {
            return mint(0);
        }
        
        return mint(x).pow(y);
    }
};

int N = 5000;
ModFac mf(N);

void solve() {
    int n;
    mint x;
    cin >> n >> x;
    mint ans = x, add = 0;
    vector<mint> P;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        int l = s.size() - 1;
        if (s[0] == '+') {
            add += mint(stoll(s.substr(1, l)));
        } else if (s[0] == '-') {
            add -= mint(stoll(s.substr(1, l)));
        } else if (s[0] == 'x') {
            ans *= mint(stoll(s.substr(1, l)));
            P.pb(mint(stoll(s.substr(1, l))));
        } else if (s[0] == '/') {
            ans /= mint(stoll(s.substr(1, l)));
            P.pb(mint(stoll(s.substr(1, l))).inv());
        }
    }

    int len = P.size();
    vector<mint> dp(len + 1);
    dp[0] = 1;
    for (int i = 1; i <= len; i++) {
        for (int j = i; j >= 1; j--)
            dp[j] += dp[j - 1] * P[i - 1];
    }

    mint E = 0;
    for (int i = 0; i <= len; i++) 
        E += dp[i] * mf.fac[i] * mf.fac[len - i] * mf.inv_fac[len + 1];

    cout << ans + add * E << endl;

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