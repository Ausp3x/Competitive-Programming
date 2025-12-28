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

int const N = 200'000;

void solve() {
    int n;
    lng y;
    cin >> n >> y;
    lng c_max = 0;
    vector<lng> C(n), cnts(N + 1);
    for (lng &c : C) {
        cin >> c;

        c_max = max(c_max, c);
        cnts[c]++;
    }
    vector<int> prf_cnts(N + 1);
    for (int i = 1; i <= N; i++)
        prf_cnts[i] = prf_cnts[i - 1] + cnts[i];

    lng ans = -INF64;
    for (lng x = 2; x <= max(c_max, 2ll); x++) {
        lng cur = 0, dis = 0;
        for (lng c_lo = 1; c_lo <= c_max; c_lo += x) {
            lng c_hi = c_lo + x - 1;
            lng c_new = c_hi / x;

            lng change = prf_cnts[min(c_hi, lng(N))] - prf_cnts[c_lo - 1];
            lng same = cnts[c_new];
            if (change == 0)
                continue;
            cur += c_new * change;
            cur -= max(change - same, 0ll) * y;
        }

        // cout << x << ' ' << cur << endl;
    
        ans = max(ans, cur);
    }

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