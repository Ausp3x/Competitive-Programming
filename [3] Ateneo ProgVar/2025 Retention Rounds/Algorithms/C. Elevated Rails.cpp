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
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adjl(n + 1);
    for (int i = 0; i < n - 3; i++) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }
    
    int cnt = 1;
    vector<int> cc(n + 1, -1);
    vector<int> diam(7);
    vector<vector<int>> diam_dis(7, vector<int>(n + 1, INF64));
    for (int i = 1; i <= n; i++) {
        if (cc[i] != -1)
            continue;
        cc[i] = cnt;

        if (adjl[i].size() == 0) {
            diam[2 * cnt - 1] = i;
            diam[2 * cnt] = i;
            diam_dis[2 * cnt - 1][i] = 0;
            diam_dis[2 * cnt][i] = 0;
            cnt++;
            continue;
        }

        int d_max = 0;
        queue<pair<int, int>> q;
        q.push({i, 0});
        while (!q.empty()) {
            auto [cur, d] = q.front();
            q.pop();

            if (d > d_max) {
                d_max = d;
                diam[2 * cnt - 1] = cur;
            }
            for (int nxt : adjl[cur]) {
                if (cc[nxt] != -1)
                    continue;
                cc[nxt] = cnt;

                q.push({nxt, d + 1});
            }
        }
        
        d_max = 0;
        vector<bool> vst(n + 1);
        q.push({diam[2 * cnt - 1], 0});
        vst[diam[2 * cnt - 1]] = true;
        while (!q.empty()) {
            auto [cur, d] = q.front();
            q.pop();

            diam_dis[2 * cnt - 1][cur] = d;
            if (d > d_max) {
                d_max = d;
                diam[2 * cnt] = cur;
            }
            for (int nxt : adjl[cur]) {
                if (vst[nxt])
                    continue;
                vst[nxt] = true;

                q.push({nxt, d + 1});
            }
        }

        vst.clear();
        vst.resize(n + 1);
        q.push({diam[2 * cnt], 0});
        vst[diam[2 * cnt]] = true;
        while (!q.empty()) {
            auto [cur, d] = q.front();
            q.pop();

            diam_dis[2 * cnt][cur] = d;
            for (int nxt : adjl[cur]) {
                if (vst[nxt])
                    continue;
                vst[nxt] = true;

                q.push({nxt, d + 1});
            }
        }
        
        cnt++;
    }

    while (q--) {
        int x, y;
        cin >> x >> y;

        int bgn = cc[x];
        int end = cc[y];
        int mid = bgn ^ end;

        cout << max(diam_dis[2 * bgn - 1][x], diam_dis[2 * bgn][x]) + 1 + diam_dis[2 * mid - 1][diam[2 * mid]] + 1 + max(diam_dis[2 * end - 1][y], diam_dis[2 * end][y]) + 1 << endl;
    }

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