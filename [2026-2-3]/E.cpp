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

struct UnionFind {
    int n;
    vector<int> par, dis, node_cnts, edge_cnts;

    UnionFind(int n): n(n) {
        par.resize(n + 1);
        iota(par.begin(), par.end(), 0);
        dis.resize(n + 1);
        node_cnts.resize(n + 1, 1);
        edge_cnts.resize(n + 1);
    }

    int findSet(int u) {
        if (u != par[u]) {
            int root = findSet(par[u]);
            dis[u] += dis[par[u]];
            par[u] = root;
        }

        return par[u];
    }

    int getDistanceToSet(int u) {
        findSet(u);
        
        return dis[u];
    }

    bool isSameSet(int u, int v) {
        return findSet(u) == findSet(v);
    }

    void uniteSets(int u, int v) {
        u = findSet(u);
        v = findSet(v);
        if (u == v) {
            edge_cnts[u]++;
            return;
        }

        if (node_cnts[u] < node_cnts[v]) {
            swap(u, v);
        }

        par[v] = u;
        dis[v] = 1;
        node_cnts[u] += node_cnts[v];
        edge_cnts[u] += edge_cnts[v] + 1;
    }
};

struct LCA {
    int n, root, l, timer = 0;
    vector<int> dep, t_in, t_out;
    vector<vector<int>> up;
    vector<vector<lng>> wmx;

    LCA(int n, int root, map<pair<int, int>, lng> &W, const vector<vector<pair<int, lng>>> &adjl): n(n), root(root) {
        l = ceil(log2(n));
        dep.resize(n + 1);
        t_in.resize(n + 1, -1);
        t_out.resize(n + 1, -1);
        up.resize(n + 1, vector<int>(l + 1, -1));
        wmx.resize(n + 1, vector<lng>(l + 1, -INF64));

        init(root, root, 0, W, adjl);
    }

    void init(int cur, int prv, int d, map<pair<int, int>, lng> &W, const vector<vector<pair<int, lng>>> &adjl) {
        dep[cur] = d;
        t_in[cur] = timer;
        timer++;
        up[cur][0] = prv;
        wmx[cur][0] = W[{cur, prv}];
        for (int i = 1; i <= l; i++) {
            up[cur][i] = up[up[cur][i - 1]][i - 1];
            wmx[cur][i] = max(wmx[cur][i - 1], wmx[up[cur][i - 1]][i - 1]);
        }

        for (auto [nxt, w_nxt] : adjl[cur]) {
            if (nxt == prv) {
                continue;
            }

            init(nxt, cur, d + 1, W, adjl);
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

    lng getMaxW(int u, int v) const {
        int a = getLCA(u, v); 
        lng res = -INF64;
        for (int i = l; i >= 0; i--) {
            if (isAncestor(a, up[u][i])) {
                res = max(res, wmx[u][i]);
                u = up[u][i];
            }

            if (u == a)
                break;
        }
        for (int i = l; i >= 0; i--) {
            if (isAncestor(a, up[v][i])) {
                res = max(res, wmx[v][i]);
                v = up[v][i];
            }
            
            if (v == a)
                break;
        }

        return res;
    }
};

void solve() {
    lng n, m;
    cin >> n >> m;
    map<pair<int, int>, lng> W;
    vector<tuple<int, int, lng>> edgl(m);
    priority_queue<tuple<lng, int, int, int>, vector<tuple<lng, int, int, int>>, greater<tuple<lng, int, int, int>>> E;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        W[{u, v}] = w;
        W[{v, u}] = w;
        edgl[i] = {u, v, w};
        E.push({w, u, v, i});
    }

    lng ans = 0;
    UnionFind uf(n + 1);
    vector<bool> vst(m);
    vector<vector<pair<int, lng>>> t_adjl(n + 1);
    while (!E.empty()) {
        auto [w, u, v, i] = E.top();
        E.pop();
        
        if (uf.isSameSet(u, v))
            continue;

        ans += w;
        uf.uniteSets(u, v);
        vst[i] = true;
        t_adjl[u].pb({v, w});
        t_adjl[v].pb({u, w});
    }

    LCA lca(n, 1, W, t_adjl);
    for (int i = 0; i < m; i++) {
        if (vst[i]) {
            cout << ans << endl;
            continue;
        }
        
        cout << ans - lca.getMaxW(get<0>(edgl[i]), get<1>(edgl[i])) + get<2>(edgl[i]) << endl;
    }

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