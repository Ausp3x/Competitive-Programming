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
    int n, m;
    cin >> n >> m;
    int k;
    cin >> k;
    vector<int> G(k);
    for (int &g : G)
        cin >> g;

    if (m == 1) {
        cout << 1 << endl;
        return;
    }

    auto remove = [&](int msk, int i) -> int {
        return ((msk >> (i + 1)) << i) + (msk & ((1 << i) - 1));
    };

    vector<vector<vector<int>>> dp(2, vector<vector<int>>(n + 1));
    for (int i = 1; i <= n; i++) {
        dp[0][i].resize(1 << i);
        dp[1][i].resize(1 << i);

        if (i == 1) {
            dp[0][i][0] = 0;
            dp[0][i][1] = 1;
            dp[1][i][0] = 0;
            dp[1][i][1] = 1;
            continue;
        }
        
        for (int msk = 0; msk < (1 << i); msk++) {
            dp[0][i][msk] = 1;
            dp[1][i][msk] = 0;
            for (int j : G) {
                if (j > i)
                    break;

                int nxt_msk = remove(msk, j - 1);
                dp[0][i][msk] &= dp[1][i - 1][nxt_msk];
                dp[1][i][msk] |= dp[0][i - 1][nxt_msk];
            }
        }
    }

    int ans = 0;
    for (int msk = 0; msk < (1 << n); msk++)
        ans += 1 + dp[1][n][msk];

    cout << ans << endl;

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