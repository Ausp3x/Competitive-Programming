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
typedef long long    lng;
typedef __int128     lll;
template<class T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> // lower_bound and upper_bound are broken
using indexed_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, w;
    cin >> n >> w;
    vector<map<int, lng>> to_add(4);
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;

        if (c == '!') {
            int p, l, a;
            cin >> p >> l >> a;

            int p_mod4 = p % 4;
            int ap_mod4 = (p + 2) % 4;

            int q = p + l - 1;

            to_add[p_mod4][(p - p_mod4) / 4] += a;
            to_add[p_mod4][(q - p_mod4) / 4 + 1] -= a;
            if (l >= 3) {
                to_add[ap_mod4][(p + 2 - ap_mod4) / 4] -= a;
                to_add[ap_mod4][(q - ap_mod4) / 4 + 1] += a;
            }
        } else if (c == '?') {
            int p;
            cin >> p;

            int p_mod4 = p % 4;

            lng ans = 0;
            for (auto [k, v] : to_add[p_mod4]) {
                if (4 * k + p_mod4 > p)
                    break;

                ans += v;
            }

            cout << ans << endl;
        }
    }

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