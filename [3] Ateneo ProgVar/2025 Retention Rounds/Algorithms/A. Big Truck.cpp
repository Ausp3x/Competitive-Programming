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

struct FloydWarshall {
    int n;
    vector<lng> A;
    vector<vector<pair<lng, lng>>> dis;
    
    FloydWarshall(int n, vector<lng> A, vector<vector<pair<lng, lng>>> dis) : n(n), dis(dis) {
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
                    if (dis[i][k].fi + dis[k][j].fi < dis[i][j].fi) {
                        dis[i][j].fi = dis[i][k].fi + dis[k][j].fi;
                        dis[i][j].se = dis[i][k].se + dis[k][j].se;
                    } else if (dis[i][k].fi + dis[k][j].fi == dis[i][j].fi) {
                        dis[i][j].se = max(dis[i][j].se, dis[i][k].se + dis[k][j].se);
                    }
                }
            }
        }
    }
};

void solve() {
    int n;
    cin >> n;
    vector<lng> A(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> A[i];
    int m;
    cin >> m;
    vector<vector<pair<lng, lng>>> adjm(n + 1, vector<pair<lng, lng>>(n + 1, {INF64, 0}));
    while (m--) {
        int a, b, d;
        cin >> a >> b >> d;
        
        adjm[a][b] = {d, A[a]};
        adjm[b][a] = {d, A[b]};
    }

    FloydWarshall fn(n, A, adjm);
    fn.runFloydWarshall(1, n);

    if (fn.dis[1][n].fi == INF64) {
        cout << "impossible" << endl;
        return;
    }

    cout << fn.dis[1][n].fi << ' ' << fn.dis[1][n].se + A[n] << endl;

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