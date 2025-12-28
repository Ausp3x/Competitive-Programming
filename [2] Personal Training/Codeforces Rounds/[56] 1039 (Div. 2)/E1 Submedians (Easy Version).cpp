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
    int n, k;
    cin >> n >> k;
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> A[i];

    int l = 0, r = n + 1;
    int x = -1, y = -1;
    vector<int> prf(n + 1);
    while (r - l > 1) {
        int md = (l + r) / 2;

        for (int i = 1; i <= n; i++) {
            if (A[i] >= md) {
                prf[i] = 1;
            } else {
                prf[i] = -1;
            }

            prf[i] += prf[i - 1];
        }

        int mn = 0, mn_i = 1, mx = prf[k];
        int cur_x = 1, cur_y = k;
        for (int i = k + 1; i <= n; i++) {
            if (prf[i - k] < mn) {
                mn = prf[i - k];
                mn_i = i - k + 1;
            }
            if (prf[i] - mn > mx) {
                mx = prf[i] - mn;
                cur_x = mn_i;
                cur_y = i;
            }
        }

        if (mx >= 0) {
            l = md;
            x = cur_x;
            y = cur_y;
        } else {
            r = md;
        }
    }

    cout << l << ' ' << x << ' ' << y << endl;

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