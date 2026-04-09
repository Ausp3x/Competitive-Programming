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

struct FloydWarshall {
    int n;
    vector<vector<lng>> dis;
    
    FloydWarshall(int n, const vector<vector<lng>> &dis) : n(n), dis(dis) {
        assert(dis.size() == n + 1);
        for (int i = 0; i <= n; i++) {
            assert(dis[i].size() == n + 1);
        }
    }
    
    void runFloydWarshall() {
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dis[i][k] < INF64 && dis[k][j] < INF64) {
                        dis[i][j] = max(min(dis[i][j], dis[i][k] + dis[k][j]), -INF64);
                    }
                }
            }
        }
    
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    if (dis[i][k] < INF64 && dis[k][k] < 0 && dis[k][j] < INF64) {
                        dis[i][j] = -INF64;
                        break;
                    }
                }
            }
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector adjm(n + 1, vector<lng>(n + 1, INF64));
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;

        adjm[u][v] = w;
    }

    FloydWarshall flw(n, adjm);

    flw.runFloydWarshall();

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++)
    //         cout << flw.dis[i][j] << ' ';
    //     cout << endl;
    // }

    int N = 1 << n;
    vector memo(N, vector<lng>(n, INF64 + 1));
    for (int i = 0; i < n; i++)
        memo[1 << i][i] = 0;

    auto dp = [&](int cur, int cl, auto &&dp) -> void {
        if (memo[cur][cl] != INF64 + 1)
            return;

        int prv = cur - (1 << cl);
        for (int pl = 0; pl < n; pl++) {
            if (!(prv & (1 << pl)))
                continue;

            dp(prv, pl, dp);
            
            memo[cur][cl] = min(memo[cur][cl], min(memo[prv][pl] + flw.dis[pl + 1][cl + 1], INF64));
        }
    };

    for (int i = 0; i < n; i++)
        dp(N - 1, i, dp);

    lng ans = INF64;
    for (int i = 0; i < n; i++)
        ans = min(ans, memo[N - 1][i]);

    if (ans > INF64 / 2) {
        cout << "No" << endl;
        return;
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

    return 0;
}