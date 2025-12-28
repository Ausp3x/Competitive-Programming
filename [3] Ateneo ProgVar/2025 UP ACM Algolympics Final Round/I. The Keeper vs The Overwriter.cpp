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
    int n, q;
    cin >> n >> q;
    map<lng, lng> cnts;
    map<lng, map<lng, pair<lng, lng>>> last;
    while (q--) {
        lng i, x;
        cin >> i >> x;

        cnts[i]++;
        if (!last[i].contains(x)) {
            last[i][x] = {cnts[i], cnts[i]};
        } else {
            last[i][x].se = cnts[i];
        }
    }

    lng ans = 0;
    for (auto &[k, v] : last) {
        lng cur = 0;
        for (auto &[k2, v2] : v) {
            cur = max(cur, v2.se - v2.fi + 1);
        } 

        ans += cnts[k] - cur;
    }
    
    cout << ans << endl;

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