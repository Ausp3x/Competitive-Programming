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
    lng xb, yb;
    cin >> xb >> yb;
    lng x, y, X, Y;
    cin >> x >> y >> X >> Y;

    if (gcd(xb, yb) == 1) {
        cout << "Yes" << endl;
        return;
    }

    auto isInside = [&](lng x_cur, lng y_cur) -> bool {
        if (x_cur < x || X < x_cur || y_cur < y || Y < y_cur)
            return false;

        return true;
    };

    lng g = gcd(xb, yb);
    lng xb0 = xb / g, yb0 = yb / g;
    if (!isInside(xb0, yb0)) {
        cout << "No" << endl;
        cout << xb0 << ' ' << yb0 << endl;
        return;
    }

    bool chk = false;
    lng l = 1, r = g;
    while (r - l > 1) {
        lng md = (l + r) / 2;
        if (!isInside(xb0 * md, yb0 * md)) {
            chk = true;
            r = md;
        } else {
            l = md;
        }
    }

    if (chk) {
        cout << "No" << endl;
        cout << xb0 * r << ' ' << yb0 * r << endl;
        return;
    }
    
    cout << "Yes" << endl;
    
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