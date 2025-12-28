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
            par[u] = findSet(par[u]);
            dis[u] += dis[par[u]];
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

void solve() {
    int n, q;
    cin >> n >> q;
    int q_ord = 0;
    deque<vector<int>> Q;
    vector<pair<int, vector<int>>> ops;
    for (int i = 0; i < q; i++) {
        char x;
        cin >> x;
        if (x == 'A') {
            int u, v;
            cin >> u >> v;
            ops.pb({x, {u, v}});
        } else if (x == '?') {
            int u, v;
            cin >> u >> v;
            ops.pb({x, {u, v, q_ord}});
            q_ord++;
        } else if (x == 'C') {
            ops.pb({x, {}});
        } else if (x == 'Q') {
            int s, u, v;
            cin >> s >> u >> v;
            Q.pb({s, u, v, q_ord});
            q_ord++;
        }
    }

    sort(Q.begin(), Q.end());

    int ctr = 0;
    string ans = string(q_ord, 'N');
    UnionFind uf(n);
    
    while (!Q.empty()) {
        if (Q[0][0] > ctr)
            break;

        int s = Q[0][0], u = Q[0][1], v = Q[0][2], q_ord = Q[0][3];
        Q.pop_front();
        
        ans[q_ord] = (uf.isSameSet(u, v) ? 'Y' : 'N');
    }
    for (int i = 0; i < ops.size(); i++) {
        char x = ops[i].fi;
        if (x == 'A') {
            int u = ops[i].se[0], v = ops[i].se[1];
            
            uf.uniteSets(u, v);
        } else if (x == '?') {
            int u = ops[i].se[0], v = ops[i].se[1], q_ord = ops[i].se[2]; 
            
            ans[q_ord] = (uf.isSameSet(u, v) ? 'Y' : 'N');
        } else if (x == 'C') {
            ctr++;
            while (!Q.empty()) {
                if (Q[0][0] > ctr)
                    break;

                int s = Q[0][0], u = Q[0][1], v = Q[0][2], q_ord = Q[0][3];
                Q.pop_front();
                
                ans[q_ord] = (uf.isSameSet(u, v) ? 'Y' : 'N');
            }
        } else if (x == 'Q') {
            int s, u, v;
            cin >> s >> u >> v;
            ops.pb({x, {s, u, v}});
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