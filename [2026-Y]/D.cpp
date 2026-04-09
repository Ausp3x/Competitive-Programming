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
    string s;
    cin >> s;
    int n = s.size();

    vector is_palin(n, vector<bool>(n));
    for (int i = 0; i < n; i++) {
        is_palin[i][i] = true;
        
        for (int j = 1; i - j >= 0 && i + j < n; j++)
            if (s[i - j] == s[i + j]) {
                is_palin[i - j][i + j] = true;
            } else {
                break;
            }
    
        for (int j = 1; i - j + 1 >= 0 && i + j < n; j++)
            if (s[i - j + 1] == s[i + j]) {
                is_palin[i - j + 1][i + j] = true;
            } else {
                break;
            }
    }

    // for (int i = 0; i < n; i++)
    //     for (int j = i; j < n; j++)
    //         cout << i << ' ' << j << ": " << is_palin[i][j] << endl;
    // cout << endl;

    vector memo(n, vector<int>(n, -1));
    auto dp = [&](int l, int r, auto &&dp) -> void {
        if (memo[l][r] != -1) {
            return;
        }

        if (l == r) {
            memo[l][r] = 1;
            return;
        }

        int d = (r - l + 1) / 2;
        int md = (l + r) / 2 + 1;

        if (!is_palin[l][r]) {
            memo[l][r] = 0;
            return;
        }

        dp(l,  l + d - 1,  dp);
        dp(md, md + d - 1, dp);

        if (memo[l][l + d - 1] == memo[md][md + d - 1]) {
            memo[l][r] = memo[l][l + d - 1] + 1;
        } else {
            memo[l][r] = 1;
        }
    };

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            dp(i, j, dp);

    // for (int i = 0; i < n; i++)
    //     for (int j = i; j < n; j++)
    //         cout << i << ' ' << j << ": " << memo[i][j] << endl;
    // cout << endl;

    vector<int> ans(n + 1);
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            ans[memo[i][j]]++;
    for (int i = n - 1; i >= 0; i--)
        ans[i] += ans[i + 1];

    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    cout << endl;

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