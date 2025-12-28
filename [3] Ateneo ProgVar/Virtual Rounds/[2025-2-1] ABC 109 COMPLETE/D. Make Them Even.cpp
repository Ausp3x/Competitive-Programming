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
    int h, w;
    cin >> h >> w;
    vector<vector<int>> grid(h + 1, vector<int>(w + 1));
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
            cin >> grid[i][j];

    vector<vector<int>> ans;
    for (int i = h; i >= 1; i--)
        for (int j = w; j >= 1; j--) {
            if (j == 1) {
                if (i > 1 && grid[i][j] % 2 != 0) {
                    grid[i][j]--;
                    grid[i - 1][j]++;
                    ans.pb({i, j, i - 1, j});
                }
            } else {
                if (grid[i][j] % 2 != 0) {
                    grid[i][j]--;
                    grid[i][j - 1]++;
                    ans.pb({i, j, i, j - 1});
                }
            }
        }

    // for (int i = 1; i <= h; i++) {
    //     for (int j = 1; j <= w; j++)
    //         cout << grid[i][j] << ' ';
    //     cout << endl;
    // }

    cout << ans.size() << endl;
    for (auto x : ans) {
        for (int i = 0; i < 3; i++)
            cout << x[i] << ' ';
        cout << x[3] << endl;
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