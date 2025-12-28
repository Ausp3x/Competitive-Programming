// 人外有人，天外有天
// author: Ausp3x

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

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adjl(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }

    vector<int> par(n), dep(n);
    auto dfs = [&](int cur, int prv, int d, auto &&dfs) {
        if (false)
            return;
        
        par[cur] = prv;
        dep[cur] = d;
        for (int nxt : adjl[cur]) {
            if (nxt == prv)
                continue;

            dfs(nxt, cur, d + 1, dfs);            
        }
    };

    dfs(0, -1, 0, dfs);

    set<pair<int, int>> S;
    for (int i = 0; i < n; i++)
        if (dep[i] > 2)
            S.insert({-dep[i], i});

    int ans = 0;
    while (!S.empty()) {
        int cur = S.begin()->se;
        cur = par[cur];

        ans++;
        S.erase(make_pair(-dep[cur], cur));
        for (auto nxt : adjl[cur])
            S.erase(make_pair(-dep[nxt], nxt));
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