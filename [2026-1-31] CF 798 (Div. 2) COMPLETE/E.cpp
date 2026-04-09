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

int k = 30;

void solve() {
    int n;
    cin >> n;
    vector<int> A(n);
    for (int &a : A)
        cin >> a;

    int ans = 0;
    for (int &a : A)
        if (a == 0) {
            ans++;
            a++;
        }

    auto isConnected = [&]() -> bool {
        UnionFind uf(n + k);
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < k; j++) 
                if (A[i] & (1 << j))
                    uf.uniteSets(j, i + k);

        bool res = true;
        for (int i = k + 1; i < n + k; i++)
            res &= uf.isSameSet(k, i);

        return res;
    };
    
    auto print = [&]() -> void {
        for (int x : A)
            cout << x << ' ';
        cout << endl;
        
        return;
    };

    if (isConnected()) {
        cout << ans << endl;
        print();
        return;
    }
    
    for (int i = 0; i < n; i++) {
        A[i]++;

        if (isConnected()) {
            cout << ans + 1 << endl;
            print();
            return;
        }

        A[i] -= 2;

        if (isConnected()) {
            cout << ans + 1 << endl;
            print();
            return;
        }

        A[i]++;
    }

    vector<pair<int, int>> B;
    for (int i = 0; i < n; i++) 
        B.push_back({A[i] & -A[i], i});
    
    sort(B.begin(), B.end(), greater<pair<int, int>>());

    A[B[0].se]++;
    A[B[1].se]--;

    cout << ans + 2 << endl;
    print();

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