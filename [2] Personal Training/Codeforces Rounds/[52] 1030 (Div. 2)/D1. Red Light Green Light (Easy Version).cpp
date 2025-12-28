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
    lng n, k;
    cin >> n >> k;
    vector<lng> P(n);
    for (lng &p : P)
        cin >> p;
    vector<lng> D(n);
    for (lng &d : D)
        cin >> d;

    vector<vector<lng>> dis(2 * n, vector<lng>(2 * n, INF64));
    // approach from right (moving left)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) 
            if ((P[j] - P[i]) % k == (D[j] - D[i] + k) % k) {
                dis[i][j + n] = 1;
                break;
            }
    }
    // approach from left (moving right)
    for (int i = 0; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) 
            if ((P[i] - P[j]) % k == (D[j] - D[i] + k) % k) {
                dis[i + n][j] = 1;
                break;
            }
    }

    // for (int i = 0; i < 2 * n; i++) {
    //     for (int j = 0; j < 2 * n; j++)
    //         cout << (dis[i][j] == INF64 ? 0 : dis[i][j]) << ' ';
    //     cout << endl;
    // }
    // cout << endl;
    
    FloydWarshall fw(2 * n - 1, dis);
    fw.runFloydWarshall(0, 2 * n - 1);

    // for (int i = 0; i < 2 * n; i++) {
    //     for (int j = 0; j < 2 * n; j++)
    //         cout << (fw.dis[i][j] == INF64 ? 0 : fw.dis[i][j]) << ' ';
    //     cout << endl;
    // }
    // cout << endl;

    int q;
    cin >> q;
    vector<lng> A(q);
    for (lng &a : A)
        cin >> a;

    for (int i = 0; i < q; i++) {
        bool has_verdict = false;
        for (int j = 0; j < n; j++) {
            if (P[j] < A[i])
                continue;

            if ((P[j] - A[i]) % k == D[j]) {
                // cout << A[i] << ' ' << P[j] << endl;
                if (fw.dis[j + n][j + n] == INF64) {
                    cout << "YES" << endl;
                } else {
                    cout << "NO" << endl;
                }
                
                has_verdict = true;
                break;
            }
        }

        if (!has_verdict)
            cout << "YES" << endl;
    }
    // cout << endl;
    
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