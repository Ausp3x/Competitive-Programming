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
    static int MOD;

    ModInt(lng x = 0) {
        val = x % MOD;
        if (val < 0) { 
            val += MOD;
        }
    }

    ModInt(const ModInt &other) : val(other.val) {}
    
    static void setMod(int mod) {
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
        val = (val * other.val) % MOD;

        return *this;
    }
    
    ModInt inv() const {
        assert(gcd(val, MOD) == 1);
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
        val = (val * other.inv().val) % MOD;

        return *this;
    }

    ModInt pow(long long exp) const {
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
int ModInt::MOD = 1'000'000'007;

void solve() {
    int n;
    cin >> n;
    vector<int> par(n + 1);
    vector<vector<int>> adjl(n + 1);
    for (int nxt = 1; nxt <= n; nxt++) {
        int cur;
        cin >> cur;

        par[nxt] = cur;
        adjl[cur].pb(nxt);
    }

    vector<int> path;
    vector<int> cycle(n + 1, -1), status(n + 1);
    vector<ModInt> ways(n + 1);
    
    auto calc = [&](int cur, auto &&calc) -> ModInt {
        ModInt res = 1;
        for (int nxt : adjl[cur])
            res *= calc(nxt, calc) + ModInt(1);

        return res;
    };

    auto dfs = [&](int cur, auto &&dfs) -> void {
        if (status[cur] == 2) {
            // complete
            return;
        }
        
        if (status[cur] == 1) {
            for (int i = path.size() - 1; i >= 0; i--) {
                cycle[path[i]] = cur;
                if (path[i] == cur)
                    break;
            }
            ways[cur] = 1;

            return;
        }
        
        path.pb(cur);
        status[cur] = 1;
        int prv = par[cur];
        dfs(prv, dfs);

        if (cycle[prv] != -1 && cycle[cur] == -1) {
            ways[cycle[prv]] *= calc(cur, calc) + ModInt(1);
        }

        status[cur] = 2;
        path.pop_back();
    };

    for (int cur = 1; cur <= n; cur++)
        dfs(cur, dfs);
    
    ModInt ans = 1;
    for (int i = 1; i <= n; i++)
        ans *= (ways[i] + 1);

    cout << ans - ModInt(1) << endl;

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