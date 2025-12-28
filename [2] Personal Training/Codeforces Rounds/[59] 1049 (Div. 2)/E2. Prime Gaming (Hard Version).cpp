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

lng const MOD = 1'000'000'007;

lng modPow(lng bse, lng exp, lng mod) {
    if (exp < 0)
        return -1;
    
    bse %= mod;
    lng res = 1;
    while (exp > 0) {
        if (exp & 1) {
            res *= bse;
            res %= mod;
        }
        
        bse *= bse;
        bse %= mod;
        exp >>= 1;
    }

    return res;
}

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

    vector<lng> cnt(n + 1);
    for (int msk = 0; msk < (1 << n); msk++) { 
        if (dp[1][n][msk] == 0)
            continue;

        int r = 0;
        for (int i = 0; i < n; i++)
            if (msk & (1 << i))
                r++;

        cnt[r]++;
    }

    lng ans = 0;
    for (int k = 1; k <= m; k++) 
        for (int r = 1; r <= n; r++) {
            ans += modPow(m - k + 1, r, MOD) * modPow(k - 1, n - r, MOD) % MOD * cnt[r] % MOD;
            ans %= MOD;
        }

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