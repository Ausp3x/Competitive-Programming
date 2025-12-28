// 人外有人，天外有天
// author: Ausp3x

#pragma GCC optimize("O1, O2, O3, Ofast, unroll-loops")
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
    int n, r, c;
    cin >> n >> r >> c;

    vector<vector<int>> grid(n + 2, vector<int>(n + 2, -1));
    grid[r][c] = 1;
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= n + 1; j++)
            if (i == 0 || i == n + 1 || j == 0 || j == n + 1)
                grid[i][j] = INF32;

    vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    queue<pair<int, int>> bfs;
    bfs.push({r, c});
    while (!bfs.empty()) {
        auto [r_cur, c_cur] = bfs.front();
        bfs.pop();

        int min_dis = INF32;
        vector<int> dis(4);
        for (int i = 0; i < 4; i++) {
            int r_tmp = r_cur, c_tmp = c_cur;
            while (grid[r_tmp + dir[i].fi][c_tmp + dir[i].se] == -1) {
                dis[i]++;

                r_tmp += dir[i].fi;
                c_tmp += dir[i].se;
            }

            if (dis[i] == 0)
                dis[i] = INF32;

            min_dis = min(min_dis, dis[i]);
        }

        if (min_dis == INF32) {
            if (grid[r_cur][c_cur] == n * n)
                break;

            // break;

            cout << "NO" << endl; // << ' ' << r << ' ' << c << endl;
            return;
        }

        priority_queue<pair<int, int>> pq;
        for (int i = 0; i < 4; i++) {
            if (dis[i] != min_dis)
                continue;
            
            int cnt = 0;
            int r_tmp = r_cur + dir[i].fi, c_tmp = c_cur + dir[i].se;
            for (int j = 0; j < 4; j++)
                cnt += grid[r_tmp + dir[j].fi][c_tmp + dir[j].se] != -1;

            pq.push({cnt, i});
        }

        int r_nxt = r_cur + dir[pq.top().se].fi, c_nxt = c_cur + dir[pq.top().se].se; 
        grid[r_nxt][c_nxt] = grid[r_cur][c_cur] + 1;
        bfs.push({r_nxt, c_nxt});
    }

    cout << "YES" << endl; // << ' ' << r << ' ' << c << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << grid[i][j] << ' ';
        cout << endl;
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