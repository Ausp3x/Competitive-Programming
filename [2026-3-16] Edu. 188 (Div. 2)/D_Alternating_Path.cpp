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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adjl(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }

    int ans = 0;
    vector<int> clr(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (clr[i] != -1)
            continue;

        bool is_bipartite = true;
        vector<int> cnts(2);
        queue<pair<int, int>> q;
        clr[i] = 0;
        cnts[0]++;
        q.push({i, i});
        while (!q.empty()) {
            auto [cur, prv] = q.front();
            q.pop();

            for (int nxt : adjl[cur]) {
                if (nxt == prv)
                    continue;

                if (clr[nxt] != -1) {
                    if (clr[nxt] != clr[cur] ^ 1)
                        is_bipartite = false;
                    continue;
                }

                clr[nxt] = clr[cur] ^ 1;
                cnts[clr[cur] ^ 1]++;
                q.push({nxt, cur});
            }
        }

        if (is_bipartite)
            ans += max(cnts[0], cnts[1]);
    }

    cout << ans << endl;

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