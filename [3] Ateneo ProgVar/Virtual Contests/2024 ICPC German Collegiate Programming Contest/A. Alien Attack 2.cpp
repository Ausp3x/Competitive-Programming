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
typedef long long    lng;
typedef __int128     lll;
template<class T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> // lower_bound and upper_bound are broken
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
    int n, m;
    cin >> n >> m;
    UnionFind uf(n);
    while (m--) {
        int i, j;
        cin >> i >> j;
        
        uf.uniteSets(i, j);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, uf.node_cnts[i]);
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