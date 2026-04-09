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

struct LCA {
    int n, root, l, timer = 0;
    vector<int> dep, t_in, t_out;
    vector<vector<int>> up;

    LCA(int n, int root, const vector<vector<int>> &adjl): n(n), root(root) {
        l = ceil(log2(n));
        dep.resize(n + 1);
        t_in.resize(n + 1, -1);
        t_out.resize(n + 1, -1);
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

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adjl(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        
        adjl[a].pb(b);
        adjl[b].pb(a);
    }
    vector<int> A(n + 1);
    unordered_map<int, unordered_set<int>> M;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];

        M[A[i]].insert(i);
    }

    lng ans = 0;
    vector<lng> cnt(n + 1);
    auto dfs = [&](int cur, int prv, int a, auto &&dfs) -> void {
        cnt[cur] = M[a].find(cur) != M[a].end();
        for (int nxt : adjl[cur]) {
            if (nxt == prv)
                continue;

            dfs(nxt, cur, a, dfs);

            cnt[cur] += cnt[nxt];
        }

        if (cur != 1) {
            ans += cnt[cur] * (M[a].size() - cnt[cur]);
        }

        return;
    };

    LCA lca(n, 1, adjl);
    auto calc = [&](int a) {
        vector<int> U;
        for (int u : M[a])
            U.pb(u);

        for (int i = 0; i < U.size(); i++)
            for (int j = i + 1; j < U.size(); j++) {
                int v = lca.getLCA(U[i], U[j]);
                ans += lca.dep[U[i]] + lca.dep[U[j]] - 2 * lca.dep[v];
            }
    };

    int k = sqrt(n);
    for (auto &[a, v] : M) {
        if (v.size() >= k) {
            dfs(1, 1, a, dfs);
        } else {
            calc(a);
        }
    }
    
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