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

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adjl(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }

    vector<int> siz(n + 1);
    auto dfs = [&](int cur, int prv, auto &&dfs) -> void {
        siz[cur] += 1;
        for (int nxt : adjl[cur]) {
            if (nxt == prv)
                continue;
            
            dfs(nxt, cur, dfs);
            siz[cur] += siz[nxt];
        }
        
        return;
    };

    dfs(1, 1, dfs);

    vector<int> dp(n + 1);
    auto calc = [&](int cur, int prv, auto &&calc) -> void {
        vector<int> N;
        for (int nxt : adjl[cur]) {
            if (nxt == prv)
                continue;

            N.pb(nxt);
            calc(nxt, cur, calc);
        }

        if (N.empty())
            return;

        if (N.size() == 1) {
            dp[cur] = siz[N[0]] - 1;
            return;
        }

        dp[cur] = max(dp[N[0]] + siz[N[1]] - 1, dp[N[1]] + siz[N[0]] - 1);
        return;
    };

    calc(1, 1, calc);

    cout << dp[1] << endl;

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