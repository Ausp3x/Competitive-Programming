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
    int n;
    cin >> n;
    map<int, int> M;
    vector<int> A(n + 1), prv(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        
        prv[i] = M[A[i]];
        M[A[i]] = i;
    }

    if (M.size() == n) {
        cout << -1 << endl;
        return;
    }

    vector<int> dp(n + 1);
    vector<pair<int, int>> R(n + 1);
    R[0] = {1, 1};
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        R[i] = R[i - 1];
        R[i].se++; 
        if (prv[i] > 0)
            if (dp[prv[i] - 1] + 1 > dp[i]) {
                dp[i] = dp[prv[i] - 1] + 1;
                R[i] = {prv[i], i};
            }
    }

    cout << dp[n] << endl;
    int j = n;
    for (int i = 0; i < dp[n]; i++) {
        cout << (i < dp[n] - 1 ? R[j].fi : 1) << ' ' << R[j].se << endl;
        j = R[j].fi - 1; 
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