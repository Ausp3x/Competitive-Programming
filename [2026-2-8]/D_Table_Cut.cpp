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
    lng n, m;
    cin >> n >> m;
    lng sum = 0;
    vector<vector<lng>> grid(n, vector<lng>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            sum += grid[i][j];
        }

    lng l = sum / 2;
    vector<lng> down = {m - 1};
    for (int i = n - 1; i >= 0; i--) {
        lng cur = -1;
        for (int j = 0; j <= min(m - 1, down.back()); j++)
            if (l - grid[i][j] >= 0) {
                l -= grid[i][j];
                cur++;
            } else {
                break;
            }

        down.pb(cur);
    }

    reverse(down.begin(), down.end());
    down.pop_back();

    // for (int d : down)
    //     cout << d << ' ';
    // cout << endl;
    
    cout << sum / 2 * (sum - sum / 2) << endl;
    int r = -1;
    string ans;
    for (int d : down) {
        ans += string(d - r, 'R');
        ans += 'D';
        r = d;
    }
    ans += string(m - 1 - r, 'R');

    assert(ans.size() == n + m);

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