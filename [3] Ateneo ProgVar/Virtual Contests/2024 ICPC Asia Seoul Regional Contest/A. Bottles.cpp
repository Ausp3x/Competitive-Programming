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
    vector<vector<int>> A(n, vector<int>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> A[i][j];
            A[i][j] += A[i][j - 1];
            // cout << A[i][j] << ' ';
        }
        // cout << endl;
    }

    for (int j = 1; j <= m; j++) {
        vector<pair<int, int>> V;
        for (int i = 0; i < n; i++) {
            V.pb({A[i][j - 1] + 1, 1});
            V.pb({A[i][j] + 1, -1});
        }

        sort(V.begin(), V.end());

        int ans = 0, cur = 0;
        for (int i = 0; i < 2 * n; i++) {
            // cout << V[i].fi * V[i].se << ' ';
            cur += V[i].se;
            ans = max(ans, cur);
        }
        // cout << endl;

        cout << ans << ' ';
    }
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