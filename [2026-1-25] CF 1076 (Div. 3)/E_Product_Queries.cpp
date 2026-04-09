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

int N = 300'000;
vector<vector<pair<lng, lng>>> P(N + 1);

void solve() {
    int n;
    cin >> n;
    set<lng> A;
    for (int i = 0; i < n; i++) {
        lng a;
        cin >> a;

        A.insert(a);
    }

    vector<lng> ans(n + 1, INF64);
    for (int i = 1; i <= n; i++) {
        if (A.find(i) != A.end()) {
            ans[i] = 1;
            continue;
        }

        for (auto &[x, y] : P[i]) {
            if (ans[x] == INF64 || ans[y] == INF64)
                continue;

            // cout << i << ": " << x << ' ' << y << ' ' << ans[x] << ' ' << ans[y] << endl;
            ans[i] = min(ans[i], ans[x] + ans[y]);
        }
    }
    
    for (int i = 1; i <= n; i++)
        cout << (ans[i] != INF64 ? ans[i] : -1) << ' ';
    cout << endl;
    // cout << endl;
    
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (lng i = 2; i <= N; i++) 
        for (lng j = 2; j * j <= i; j++) {
            if (i % j != 0)
                continue;

            P[i].pb({j, i / j});
        }

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}