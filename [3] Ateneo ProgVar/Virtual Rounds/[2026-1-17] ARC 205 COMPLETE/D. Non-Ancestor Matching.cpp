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
    vector<int> par(n + 1);
    vector<vector<int>> adjl(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> par[i];

        adjl[par[i]].pb(i);
        adjl[i].pb(par[i]);
    }

    // for (int x : par)
    //     cout << x << ' ';
    // cout << endl;

    vector<int> siz(n + 1);
    auto dfs = [&](int cur, auto &&dfs) -> void {
        siz[cur] = 1;
        for (int nxt : adjl[cur]) {
            if (nxt == par[cur])
                continue;

            dfs(nxt, dfs);

            siz[cur] += siz[nxt];
        }

        return;
    };

    dfs(1, dfs);

    int ans = 0, cur = 1, debt = 0;
    while (true) {
        if (debt > 0) {
            ans++;
            debt--;
        }

        int sum = 0;
        priority_queue<pair<int, int>> pq;
        for (auto nxt : adjl[cur]) {
            if (nxt == par[cur])
                continue;

            sum += siz[nxt];
            pq.push({siz[nxt], nxt});
        }

        if (pq.empty())
            break;
        auto [nxt_siz, nxt] = pq.top();

        // cout << nxt << ' '<< nxt_siz << ' ' << sum - nxt_siz << endl;
    
        if (2 * nxt_siz <= sum + debt) {
            ans += (sum + debt) / 2;
            break;
        }

        cur = nxt;
        debt += sum - nxt_siz;
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