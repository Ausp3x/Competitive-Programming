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
    vector<vector<int>> adjl(n + 1);
    while (m--) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }

    int t = 0;
    vector<vector<int>> f(2, vector<int>(n + 1, INF32));
    f[0][1] = 0;
    for (int _ = 0; _ < 5 * n; _++) {
        int t_mod2 = t & 1;
        if (f[t_mod2][n] != INF32) {
            cout << t << ' ' << f[t_mod2][n] << endl;
            return;
        }
        
        for (int i = 1; i <= n; i++) 
            f[t_mod2 ^ 1][i] = INF32;

        for (int u = 1; u <= n; u++) {
            int v = adjl[u][t % adjl[u].size()];

            f[t_mod2 ^ 1][u] = min(f[t_mod2 ^ 1][u], f[t_mod2][u] + 1);
            f[t_mod2 ^ 1][v] = min(f[t_mod2 ^ 1][v], f[t_mod2][u]);
        }

        t++;
    }
    
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