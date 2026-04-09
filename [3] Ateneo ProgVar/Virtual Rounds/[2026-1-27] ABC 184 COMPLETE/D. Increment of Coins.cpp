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
    int A, B, C;
    cin >> A >> B >> C;

    deque<vector<int>> Q;
    vector P(101, vector(101, vector<double>(101)));
    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++)  
            for (int k = 0; k <= 100; k++) {
                if (i - A < 0 || j - B < 0 || k - C < 0 || i == 100 || j == 100 || k == 100)
                    continue;

                Q.pb({i + j + k - A - B - C, i, j, k});   
            }
    sort(Q.begin(), Q.end());
    P[A][B][C] = 1;
    while (!Q.empty()) {
        auto V = Q.front();
        Q.pop_front();
        // cout << V[0] << ": " << V[1] << ' ' << V[2] << ' ' << V[3] << endl;

        for (int i = 1; i <= 3; i++) 
            if (V[i] < 100)
                P[V[1] + (i == 1)][V[2] + (i == 2)][V[3] + (i == 3)] += P[V[1]][V[2]][V[3]] * V[i] / (V[1] + V[2] + V[3]);
    }
    double ans = 0;
    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++)
            for (int k = 0; k <= 100; k++) 
                if ((i == 100 || j == 100 || k == 100) && P[i][j][k] != 0) {
                    // cout << i << ' ' << j << ' ' << k << ": " << P[i][j][k] << endl;
                    ans += (i + j + k - A - B - C) * P[i][j][k];
                }

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