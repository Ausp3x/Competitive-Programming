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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> C(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> C[i];
    vector<vector<int>> adjl(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }

    lng mx_dep = -1;
    map<int, lng> cnts;
    queue<pair<int, lng>> bfs;
    vector<bool> vst(n + 1);
    bfs.push({1, 0});
    vst[1] = true;
    while (!bfs.empty()) {
        auto [cur, dep] = bfs.front();
        bfs.pop();

        mx_dep = max(mx_dep, dep);
        cnts[dep]++;
        for (int nxt : adjl[cur]) {
            if (vst[nxt])
                continue;

            bfs.push({nxt, dep + 1});
            vst[nxt] = true;
        }
    }

    lng ans = -m;
    for (auto &[dep, cnt] : cnts) {
        if (cnt > 0)
            ans += cnt * (cnt - 1) / 2;
        if (dep < mx_dep)
            ans += cnt * cnts[dep + 1];
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