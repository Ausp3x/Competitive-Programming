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
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> C(n + 2, {INF32, -INF32});
    vector grid(n + 2, vector<char>(m + 2));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 'B') {
                C[i].fi = min(C[i].fi, j);
                C[i].se = max(C[i].se, j);
            }
        }

    int i_ans = -1, j_ans = -1, d_mn = INF32;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int d = 0;
            for (int k = 1; k <= n; k++) {
                if (C[k] == pair<int, int>(INF32, -INF32))
                    continue;
                
                d = max(d, abs(k - i) + abs(C[k].fi - j));
                d = max(d, abs(k - i) + abs(C[k].se - j));
            }

            // cout << i << ' ' << j << ": " << d << endl;

            if (d < d_mn) {
                i_ans = i;
                j_ans = j;
                d_mn = d;
            }
        }

    cout << i_ans << ' ' << j_ans << endl;

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