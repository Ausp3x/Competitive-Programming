// 人外有人，天外有天
// author: Ausp3x

#pragma GCC optimize("O3, fast-math")
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

int const MOD = 998244353;

void solve() {
    string s;
    cin >> s;
    int n;
    cin >> n;

    vector<vector<vector<lng>>> dp(n, vector<vector<lng>>(2, vector<lng>(2)));
    dp[0][0][0] = 1;
    dp[0][0][1] = 1;
    for (int i = 0; i < n - 1; i++) 
        for (int j : {0, 1})
            for (int k : {0, 1}) {
                if (!(j == 1 && k == 1)) 
                    (dp[i + 1][k][0] += dp[i][j][k]) %= MOD;
                (dp[i + 1][k][1] += dp[i][j][k]) %= MOD;
            }

    cout << (dp[n - 1][0][0] + dp[n - 1][0][1] + dp[n - 1][1][0] + dp[n - 1][1][1]) % MOD << endl;
    
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