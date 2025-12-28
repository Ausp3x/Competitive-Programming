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
    int p, s;
    cin >> p >> s;
    
    for (int h = 1; h <= 200; h++) {
        for (int w = h; w <= h + 1; w++) {
            int cur_p = 2 * (h + w), l = h + w - 1, r = h * w;
            for (int cur_s = l; cur_s <= r; cur_s++) {
                if (cur_p * s != p * cur_s)
                    continue;

                cout << cur_s << endl;
                for (int j = 1; j <= w; j++)
                    cout << 1 << ' ' << j << endl;
                for (int i = 2; i <= h; i++)
                    cout << i << ' ' << 1 << endl;

                int cnt = cur_s - l;
                for (int i = 2; i <= h && cnt > 0; i++)
                    for (int j = 2; j <= w && cnt > 0; j++) {
                        cout << i << ' ' << j << endl;
                        cnt--;
                    }
                
                return;
            }
        }
    }

    cout << -1 << endl;

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