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
lng const INF64 = 0x3f3f3f3f3f3f3f3f / 2;

struct FloydWarshall {
    int n;
    vector<vector<lng>> dis;
    
    FloydWarshall(int n, vector<vector<lng>> dis) : n(n), dis(dis) {
        assert(dis.size() == n + 1);
        for (int i = 0; i <= n; i++) {
            assert(dis[i].size() == n + 1);
        }
    }
    
    void runFloydWarshall(int bgn, int end) {
        assert(0 <= bgn && bgn <= n);
        assert(0 <= end && end <= n);
        for (int k = bgn; k <= end; k++) {
            for (int i = bgn; i <= end; i++) {
                for (int j = bgn; j <= end; j++) {
                    if (dis[i][k] < INF64 && dis[k][j] < INF64) {
                        dis[i][j] = max(min(dis[i][j], dis[i][k] + dis[k][j]), -INF64);
                    }
                }
            }
        }
    
        for (int i = bgn; i <= end; i++) {
            for (int j = bgn; j <= end; j++) {
                for (int k = bgn; k <= end; k++) {
                    if (dis[i][k] < INF64 && dis[k][k] < 0 && dis[k][j] < INF64) {
                        dis[i][j] = -INF64;
                    }
                }
            }
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<lng>> adjm(n + 2, vector<lng>(n + 2, INF64));
    for (int i = 1; i <= n + 1; i++)
        adjm[i][i] = 0;
    while (m--) {
        int a, b;
        lng c;
        cin >> a >> b >> c;

        adjm[a][b] = min(adjm[a][b], c);
        adjm[b][a] = min(adjm[b][a], c);
    }
    
    int k;
    lng t;
    cin >> k >> t;
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;

        adjm[a][n + 1] = min(adjm[a][n + 1], t);
        adjm[n + 1][a] = min(adjm[n + 1][a], 0ll);
    }

    FloydWarshall fw(n + 1, adjm);
    fw.runFloydWarshall(1, n + 1);

    vector<vector<lng>> dis = fw.dis;

    // for (int i = 1; i <= n + 1; i++) {
    //     for (int j = 1; j <= n + 1; j++) {
    //         if (dis[i][j] == INF64)
    //             cout << "inf ";
    //         else 
    //             cout << dis[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    int q;
    cin >> q;
    while (q--) {
        int qry;
        cin >> qry;

        if (qry == 1) {
            int x, y;
            lng c;            
            cin >> x >> y >> c;

            adjm[x][y] = min(adjm[x][y], c);
            adjm[y][x] = min(adjm[y][x], c);
            
            for (int i = 1; i <= n + 1; i++) {
                for (int j = 1; j <= n + 1; j++) {
                    dis[i][j] = min(dis[i][j], dis[i][x] + adjm[x][y] + dis[y][j]);
                    dis[i][j] = min(dis[i][j], dis[i][y] + adjm[y][x] + dis[x][j]);
                }
            }
        } else if (qry == 2) {
            int x;
            cin >> x;

            adjm[x][n + 1] = min(adjm[x][n + 1], t);
            adjm[n + 1][x] = min(adjm[n + 1][x], 0ll);

            for (int i = 1; i <= n + 1; i++) {
                for (int j = 1; j <= n + 1; j++) {
                    dis[i][j] = min(dis[i][j], dis[i][x] + adjm[x][n + 1] + dis[n + 1][j]);
                    dis[i][j] = min(dis[i][j], dis[i][n + 1] + adjm[n + 1][x] + dis[x][j]);
                }
            }
        } else if (qry == 3) {
            lng f = 0;
            for (int i = 1; i <= n; i++)    
                for (int j = 1; j <= n; j++)
                    if (dis[i][j] != INF64)
                        f += dis[i][j];
        
            cout << f << endl;
        }
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