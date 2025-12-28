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
    lng h, d;
    cin >> h >> d;

    if (h == 1) {
        cout << 2 * d << endl;
        return;
    }

    lng lo = -1, hi = d + 1;
    while (hi - lo > 1) {
        lng md = (lo + hi) / 2;

        lng a = d / (md + 1);
        lng r = d % (md + 1);

        if (r * (a + 1) * (a + 2) / 2 + (md - r + 1) * a * (a + 1) / 2 > h + md - 1)
            lo = md;
        else
            hi = md; 
    }

    cout << d + hi << endl;
     
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