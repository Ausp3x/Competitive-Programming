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
    vector<pair<lng, lng>> P(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> P[i].fi >> P[i].se;

    auto getDis = [&](int a, int b) -> lng {
        return (P[b].fi - P[a].fi) * (P[b].fi - P[a].fi) + (P[b].se - P[a].se) * (P[b].se - P[a].se); 
    };

    int prv = 1;
    vector<bool> vst(n + 1);
    cout << 1 << ' ';
    vst[1] = true;
    for (int i = 0; i < n - 1; i++) {
        int cur = -1;
        lng d = 0;
        for (int j = 1; j <= n; j++) {
            if (vst[j])
                continue;

            if (getDis(prv, j) > d) {
                cur = j;
                d = getDis(prv, j);
            }
        }

        prv = cur;
        cout << prv << ' ';
        vst[prv] = true;
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