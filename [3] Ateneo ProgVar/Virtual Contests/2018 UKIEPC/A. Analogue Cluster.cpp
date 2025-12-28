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
    int n, c;
    cin >> n >> c;
    vector<int> V(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> V[i];
    vector<vector<int>> adjl(n + 1);
    while (c--) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }

    int clr = 0;
    vector<int> colors(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (colors[i] != -1)
            continue;

        auto dfs = [&](int u, auto &&dfs) {
            if (colors[u] != -1)    
                return;
            colors[u] = clr;

            for (int v : adjl[u])
                dfs(v, dfs);
        };

        dfs(i, dfs);

        clr++;
    }

    vector<int> sizes(clr);
    vector<map<int, int>> counts(clr);
    for (int i = 1; i <= n; i++) {
        sizes[colors[i]]++;
        counts[colors[i]][V[i]]++;
    }

    lng ans = 0;
    for (int i = 0; i < clr; i++) {
        int f_max = -1;
        for (auto &[v, f] : counts[i]) 
            f_max = max(f_max, f);
            
        ans += sizes[i] - f_max;
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
}