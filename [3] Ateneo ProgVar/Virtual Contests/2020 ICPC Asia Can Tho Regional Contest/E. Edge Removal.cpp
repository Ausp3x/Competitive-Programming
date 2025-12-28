// 人外有人，天外有天
// author: Ausp3x

#pragma GCC optimize("O1, O2, O3, Ofast, unroll-loops")
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
    vector<int> link, node_size, edge_size;

    UnionFind(int n): n(n) {
        link.resize(n + 1);
        iota(link.begin(), link.end(), 0);
        node_size.resize(n + 1, 1);
        edge_size.resize(n + 1);
    }

    int findSet(int u) {
        if (u == link[u]) {
            return link[u];
        }
            
        return link[u] = findSet(link[u]);
    }

    bool isSameSet(int a, int b) {
        return findSet(a) == findSet(b);
    }

    void uniteSets(int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (node_size[a] < node_size[b]) {
            swap(a, b);
        }

        if (a == b) {
            edge_size[a]++;
            return;
        }

        node_size[a] += node_size[b];
        edge_size[a] += edge_size[b] + 1;
        link[b] = a;

        return;
    }
};

struct Edge {
    int idx, u, v, w;

    Edge() {}

    bool operator<(const Edge &e) {
        return w < e.w;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Edge> E(m + 1);
    UnionFind in_dsu(n);
    for (int i = 1; i <= m; i++) {
        E[i].idx = i;
        cin >> E[i].u >> E[i].v >> E[i].w;
    
        in_dsu.uniteSets(E[i].u, E[i].v);
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++)
        cnt += in_dsu.link[i] == i;

    if (cnt > 1) {
        cout << -1 << endl;
        return;
    }

    sort(E.begin() + 1, E.end());

    // for (auto e : E)
    //     cout << e.idx << ' ' << e.w << endl;
    // cout << endl; 

    vector<int> ans;
    UnionFind fi_dsu(n);
    for (int i = 1; i <= m; ) {
        int j = i;
        while (j <= m && E[j].w == E[i].w)
            j++;

        // cout << i << ' ' << j << endl;

        vector<Edge> cands;
        for (int k = i; k < j; k++)
            if (fi_dsu.findSet(E[k].u) != fi_dsu.findSet(E[k].v))
                cands.pb(E[k]);

        for (auto e : cands) {
            if (fi_dsu.findSet(e.u) == fi_dsu.findSet(e.v))
                ans.pb(e.idx);
            else
                fi_dsu.uniteSets(e.u, e.v);
        }

        i = j;
    }

    cout << ans.size() << ' ';
    for (int x : ans)
        cout << x << ' ';
    cout << endl;

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