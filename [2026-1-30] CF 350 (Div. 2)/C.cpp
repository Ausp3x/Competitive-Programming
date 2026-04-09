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
    map<int, int> cnts;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        cnts[a]++;
    }

    int m;
    cin >> m;
    vector<int> B(m);
    for (int &b : B)
        cin >> b;
    vector<int> C(m);
    for (int &c : C)
        cin >> c;

    int ans = -1;
    pair<int, int> mx = {-1, -1};
    for (int i = 0; i < m; i++) {
        // cout << B[i] << ", " << C[i] << ": " << cnts[B[i]] << ' ' << cnts[C[i]] << endl;    
        if (cnts[B[i]] > mx.fi || (cnts[B[i]] == mx.fi && cnts[C[i]] > mx.se)) {
            ans = i;
            mx = {cnts[B[i]], cnts[C[i]]};
        }
    }

    cout << ans + 1 << endl;

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