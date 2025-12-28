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
    int h, w, r, s;
    cin >> h >> w >> r >> s;
    vector<vector<char>> grid(h, vector<char>(w));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) 
            cin >> grid[i][j];

    vector<pair<int, int>> di_dj = {{-r, 0}, {0, -r}, {0, r}, {r, 0}};
    for (int i = -r + 1; i <= r - 1; i++)
        for (int j = -r + 1; j <= r - 1; j++) 
            if (!(i == 0 && j == 0))
                di_dj.pb({i, j});
    
    sort(di_dj.begin(), di_dj.end());
            
    int idx = 0;
    map<pair<int, int>, int> loc_to_idx;
    vector<pair<int, int>> idx_to_loc;
    for (int i = h - 1; i >= 0; i--)
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == '.')
                continue;

            loc_to_idx[{i, j}] = idx;
            idx_to_loc.pb({i, j});

            idx++;
        }

    auto getDistance = [&](pair<int, int> cur, pair<int, int> nxt) -> double {
        return sqrt((nxt.fi - cur.fi) * (nxt.fi - cur.fi) + (nxt.se - cur.se) * (nxt.se - cur.se));
    };

    int n = idx, N = 9 * n;
    vector<vector<bool>> is_proc(n, vector<bool>(N + 1));
    vector<vector<double>> dis(n, vector<double>(N + 1, INF64));
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>>> unproc;
    
    auto dijkstra = [&](int src) -> void {
        int src_cost = grid[idx_to_loc[src].fi][idx_to_loc[src].se] - '0';
        dis[src][src_cost] = 0;
        unproc.push({dis[src][src_cost], {src, src_cost}});
        while (!unproc.empty()) {
            auto [cur, s_cur] = unproc.top().se;
            unproc.pop();

            if (is_proc[cur][s_cur]) {
                continue;
            }
            is_proc[cur][s_cur] = true;

            auto [ci, cj] = idx_to_loc[cur];
            for (auto [di, dj] : di_dj) {
                int ni = ci + di, nj = cj + dj;
                if (loc_to_idx.find({ni, nj}) == loc_to_idx.end())
                    continue;

                int nxt = loc_to_idx[{ni, nj}], s_nxt = s_cur + (grid[ni][nj] - '0');
                if (s_nxt > N)
                    continue;
                
                double added_dis = getDistance({ci, cj}, {ni, nj});
                if (dis[cur][s_cur] + added_dis < dis[nxt][s_nxt]) {
                    dis[nxt][s_nxt] = dis[cur][s_cur] + added_dis;
                    unproc.push({dis[nxt][s_nxt], {nxt, s_nxt}});
                }
            } 
        };

        return;
    };
    
    dijkstra(0);

    double ans = INF64;
    for (int j = 0; j <= min(N, s); j++) { 
        // cout << j << ": " << dis[n - 1][j] << endl;
        ans = min(ans, dis[n - 1][j]);
    }
    
    if (ans >= 1e12)
        cout << "impossible" << endl;
    else
        cout << setprecision(15) << ans << endl;

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