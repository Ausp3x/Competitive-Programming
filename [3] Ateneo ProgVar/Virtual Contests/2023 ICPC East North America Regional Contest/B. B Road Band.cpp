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
template<class T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int m, n, K;
    double s;
    cin >> m >> n >> K >> s;
    s /= 2;
    int len = m + n;
    vector<double> X(len + 1);
    for (int i = 1; i <= len; i++)
        cin >> X[i];

    sort(X.begin(), X.end());

    vector<double> X_sum(len + 1), X_sq_sum(len + 1);
    for (int i = 1; i <= len; i++) {
        X_sum[i] = X_sum[i - 1] + X[i];
        X_sq_sum[i] = X_sq_sum[i - 1] + X[i] * X[i];
    }

    // cout << s << endl;

    // for (auto x : X_sum)
    //     cout << x << ' ';
    // cout << endl;

    // for (auto x : X_sq_sum)
    //     cout << x << ' ';
    // cout << endl;
    
    // first i customers by distance satisfied, j towers up
    vector<vector<double>> dp(len + 1, vector<double>(K + 1, INF64));
    for (int i = 1; i <= len; i++) {
        double mean = X_sum[i] / i;
        dp[i][1] = X_sq_sum[i] - 2 * X_sum[i] * mean + i * mean * mean + i * s * s;
        for (int j = 2; j <= min(K, i); j++)
            for (int k = i - 1; k >= 1; k--) {
                if (j - 1 > k)
                    break;

                mean = (X_sum[i] - X_sum[k]) / (i - k); 
                double ext = (X_sq_sum[i] - X_sq_sum[k]) 
                             - 2 * (X_sum[i] - X_sum[k]) * mean
                             + (i - k) * mean * mean + (i - k) * s * s;
                dp[i][j] = min(dp[i][j], dp[k][j - 1] + ext);
            }
    }

    // for (int i = 1; i <= len; i++) {
    //     for (int j = 1; j <= K; j++)
    //         cout << dp[i][j] << ' ';
    //     cout << endl;
    // }

    cout << setprecision(15) << dp[len][K] << endl;
    
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