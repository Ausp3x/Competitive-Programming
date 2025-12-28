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
    int m, n, d;
    cin >> m >> n >> d;
    vector<tuple<lng, lng, lng>> points(n + d + 1);
    points.pb({-1, -1, -1});
    // resources
    for (int i = 1; i <= n; i++) {
        lng x, y;
        cin >> x >> y;

        points[i] = {x, y, 0};
    }
    // defenses
    for (int i = n + 1; i <= n + d; i++) {
        lng x, y, r;
        cin >> x >> y >> r;

        points[i] = {x, y, r};
    }

    vector<int> par(n + d + 1, -1);
    vector<vector<int>> adjl(n + d + 1);
    for (int i = n + 1; i <= n + d; i++) {
        for (int j = 1; j <= n + d; j++) {
            if (i == j)
                continue;

            auto [xi, yi, ri] = points[i];
            auto [xj, yj, rj] = points[j];
            if (ri * ri >= abs(xj - xi) * abs(xj - xi) + abs(yj - yi) * abs(yj - yi)) {
                par[j] = i;
                adjl[i].pb(j);
                adjl[j].pb(i);
            }
        }
    }

    int C = 0;
    vector<int> clrs(n + d + 1, -1);
    for (int i = 1; i <= n + d; i++) {
        if (clrs[i] != -1)
            continue;

        bool has_cycle = false;
        if (par[i] != -1)
            if (i == par[par[i]]) 
                has_cycle = true;
        
        queue<int> q;
        q.push(i);
        clrs[i] = C;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int nxt : adjl[cur]) {
                if (clrs[nxt] != -1)
                    continue;

                q.push(nxt);
                clrs[nxt] = C;
            }
        }

        if (has_cycle) {
            for (int j = 1; j <= n + d; j++)
                if (clrs[j] == C)
                    clrs[j] = -1;
        }

        C++;
    }

    for (int i = 1; i <= n + d; i++) 
        if (par[i] == -1 && clrs[i] != -1) {
            par[i] = 0;
            adjl[0].pb(i);
            adjl[i].pb(0);
        }

    vector<vector<lng>> memo(n + d + 1, {0});
    auto dfs = [&](int cur, auto &&dfs) -> void {
        if (adjl[cur].size() == 1) {
            if (cur <= n)
                memo[cur] = {0, 1};

            return;
        }

        vector<lng> X = {0};
        for (int nxt : adjl[cur]) {
            if (nxt == par[cur])
                continue;
            
            dfs(nxt, dfs);

            int len = min(int(X.size() + memo[nxt].size() - 1), n + 1);
            vector<lng> Y(len, INF64);
            for (int i = 0; i < X.size(); i++)
                for (int j = 0; j < memo[nxt].size() && i + j < len; j++) 
                    Y[i + j] = min(Y[i + j], X[i] + memo[nxt][j]);
            
            X = Y;
        }
        for (int i = 1; i < X.size(); i++)
            X[i]++;
        
        memo[cur] = X;
        
        return;
    };

    dfs(0, dfs);

    int ans = 0;
    for (int i = 0; i < memo[0].size(); i++)
        if (memo[0][i] - 1 <= m)
            ans = i;
        else
            break;

    // for (int i = 0; i < memo[0].size(); i++)
    //     cout << memo[0][i] << ' ';
    // cout << endl;

    cout << ans << endl;

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
