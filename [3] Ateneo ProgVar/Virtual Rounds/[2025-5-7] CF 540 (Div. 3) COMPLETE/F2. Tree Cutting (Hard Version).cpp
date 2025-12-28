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

struct LCA {
    int n, root, l, timer = 0;
    vector<int> dep, t_in, t_out;
    vector<vector<int>> up;

    LCA(int n, int root, const vector<vector<int>> &adjl): n(n), root(root) {
        l = ceil(log2(n));
        dep.resize(n + 1);
        t_in.resize(n + 1);
        t_out.resize(n + 1);
        up.resize(n + 1, vector<int>(l + 1, -1));

        init(root, root, 0, adjl);
    }

    void init(int cur, int prv, int d, const vector<vector<int>> &adjl) {
        dep[cur] = d;
        t_in[cur] = timer;
        timer++;
        up[cur][0] = prv;
        for (int i = 1; i <= l; i++) {
            up[cur][i] = up[up[cur][i - 1]][i - 1];
        }

        for (int nxt : adjl[cur]) {
            if (nxt == prv) {
                continue;
            }

            init(nxt, cur, d + 1, adjl);
        }

        t_out[cur] = timer - 1;
    }

    bool isAncestor(int u, int v) const {
        return t_in[u] <= t_in[v] && t_out[v] <= t_out[u];
    }

    int getKthAncestor(int u, int k) const {
        if (k <= 0) {
            return u;
        }
        
        if (k > dep[u]) {
            return -1;
        }
        
        for (int i = l; i >= 0; i--) {
            if (k & (1 << i)) {
                u = up[u][i];
            }
        }

        return u;
    }

    int getLCA(int u, int v) const {
        if (isAncestor(u, v)) {
            return u;
        }
        
        if (isAncestor(v, u)) {
            return v;
        }

        for (int i = l; i >= 0; i--) {
            if (!isAncestor(up[u][i], v)) {
                u = up[u][i];
            }
        }

        return up[u][0];
    }
};

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
int ModInt::MOD = 998'244'353;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> A[i];
    vector<vector<int>> adjl(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }

    LCA lca(n, 1, adjl);
    vector<int> clr_anc(k + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (clr_anc[A[i]] == -1)
            clr_anc[A[i]] = i;
        else
            clr_anc[A[i]] = lca.getLCA(clr_anc[A[i]], i);
    }

    for (int i = 1; i <= n; i++) {
        if (A[i] == 0)
            continue;

        int cur = i, clr = A[cur];
        while (true) {
            if (cur == clr_anc[clr])
                break;

            cur = lca.getKthAncestor(cur, 1);
            if (A[cur] != 0) {
                if (A[cur] != clr) {
                    cout << 0 << endl;
                    return;
                }
                break;
            }
            A[cur] = clr;
        }
    }

    vector<bool> vst(n + 1);
    vector<vector<ModInt>> memo(n + 1, {ModInt(0), ModInt(0)});
    auto dp = [&](int cur, int prv, auto &&dp) -> void {
        if (vst[cur])
            return;
        vst[cur] = true;
        assert(memo[cur][0] == 0 && memo[cur][1] == 0);

        if (adjl[cur].size() == 1 && cur != 1) {
            if (A[cur] == 0) {
                memo[cur][0] = ModInt(1);
                memo[cur][1] = ModInt(0);
            } else {
                memo[cur][0] = ModInt(0);
                memo[cur][1] = ModInt(1);
            }
            return;
        }
        
        ModInt M = 1;
        for (int nxt : adjl[cur]) {
            if (nxt == prv)
                continue;

            dp(nxt, cur, dp);
            M *= memo[nxt][0] + memo[nxt][1];
        }

        if (A[cur] == 0) {
            memo[cur][0] = M;
            for (int nxt : adjl[cur]) {
                if (nxt == prv)
                    continue;

                memo[cur][1] += M * memo[nxt][1] / (memo[nxt][0] + memo[nxt][1]);
            }
        } else {
            memo[cur][0] = 0;
            memo[cur][1] = M;
        }

        return;
    };

    dp(1, 1, dp);

    cout << memo[1][1] << endl;

    // for (int i = 1; i <= n; i++) {
    //     cout << i << ": (" << memo[i][0] << ", " << memo[i][1] << ')' << endl;
    // }

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