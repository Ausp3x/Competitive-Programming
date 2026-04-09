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
using mint = ModInt<998'244'353>;

void solve() {
    int n;
    cin >> n;
    vector adjl(n + 1, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }

    int root = 1;
    vector memo(n + 1, vector<mint>(4));
    auto dfs = [&](int cur, int prv, auto &&dfs) -> void {
        if (cur != root && adjl[cur].size() == 1) {
            memo[cur][0] = 1;
            memo[cur][2] = 1;

            // cout << "--- " << cur << " ---" << endl;
            // for (int i = 1; i <= n; i++)
            //     cout << i << ": " << memo[i][0] << ' ' << memo[i][1] << ' ' << memo[i][2] << ' ' << memo[i][3] << endl;
            return;
        }

        memo[cur][0] = 1;
        memo[cur][2] = 1;
        for (int nxt : adjl[cur]) {
            if (nxt == prv)
                continue;

            dfs(nxt, cur, dfs);

            memo[cur][0] *= memo[nxt][0] + memo[nxt][2];
            memo[cur][1] += memo[nxt][1] + memo[nxt][3];
            memo[cur][3] += memo[nxt][0] + memo[nxt][2] - 1;
        }
        
        // cout << "--- " << cur << " ---" << endl;
        // for (int i = 1; i <= n; i++)
        //     cout << i << ": " << memo[i][0] << ' ' << memo[i][1] << ' ' << memo[i][2] << ' ' << memo[i][3] << endl;
        return;
    };

    dfs(root, root, dfs);
    
    cout << memo[1][0] + memo[1][1] + memo[1][2] + memo[1][3] << endl;

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