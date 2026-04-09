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

// Z(i) = length longest prefix that can be formed starting from a_i
// dp(i) = f(i) = dp(j) + 1 where j is maximum possible where j < i, j + Z(j + 1) >= i
// O(nq)

void solve() {
    int n, q;
    cin >> n >> q;
    string s(n + 1, 'X');
    for (int i = 1; i <= n; i++)
        cin >> s[i];    

    while (q--) {
        int l, r;
        cin >> l >> r;

        int m = r - l + 1;
        int a = 1, b = 1;
        vector<int> Z(m + 1);
        for (int i = 2; i <= m; i++) {
            if (i <= b) {
                Z[i] = min(Z[i - a + 1], b - i + 1);
            }

            while (i + Z[i] <= m && s[l + Z[i]] == s[l + (i - 1) + Z[i]])
                Z[i]++;

            if (i + Z[i] - 1 > b) {
                a = i;
                b = i + Z[i] - 1;
            }
        }
        Z[1] = m;

        // for (int x : Z)
        //     cout << x << ' ';
        // cout << endl;

        lng ans = 0;
        stack<pair<int, int>> S;
        vector<int> dp(m + 1);
        S.push({0, Z[1]});
        for (int i = 1; i <= m; i++) {
            while (S.top().se < i && !S.empty())
                S.pop();

            dp[i] = dp[S.top().fi] + 1;
            ans += dp[i];
            if (i < m)
                S.push({i, i + Z[i + 1]});
        }

        cout << ans << endl;
    }


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