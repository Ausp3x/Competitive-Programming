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
    vector<array<int, 5>> P(n);
    for (auto &[a, b, c, d, e] : P)
        cin >> a >> b >> c >> d >> e;

    if (n >= 50) {
        cout << 0 << endl;
        return;
    }

    vector<int> ans;
    for (int i = 0; i < n; i++) {
        bool chk = true;
        for (int j = 0; j < n; j++) {
            if (j == i)
                continue;
            
            for (int k = j + 1; k < n; k++) {
                if (k == i)
                    continue;

                int dot = 0;
                for (int l = 0; l < 5; l++)
                    dot += (P[j][l] - P[i][l]) * (P[k][l] - P[i][l]);

                // cout << i << ' ' << j << ' ' << k << ' ' << dot << endl;

                if (dot > 0) {
                    chk = false;
                    break;
                }
            }

            if (!chk)
                break;
        }

        if (chk) {
            ans.pb(i + 1);
        }
    }

    cout << ans.size() << endl;
    for (int x : ans) 
        cout << x << endl;

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