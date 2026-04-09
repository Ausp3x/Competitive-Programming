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
    int n, k;
    cin >> n >> k;
    map<lng, lng> cnts;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        cnts[a]++;
    }

    lng l = 0, r = 1'000'000'001;
    while (r - l > 1) {
        lng md = (l + r) / 2;
    
        lng req = 0;
        for (auto &[a, c] : cnts) 
            req += ((a + md - 1) / md - 1) * c;

        // cout << md << ' ' << req << endl;
    
        if (req > k)
            l = md;
        else
            r = md;
    }

    cout << r << endl;

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