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
    int n;
    cin >> n;
    vector<lng> A(n);
    map<lng, lng> small, rest;
    for (auto &a : A) {
        cin >> a;
        
        if (a == 1 || a == 2 || a == 4)
            small[a]++;
        else
            rest[a]++;
    }

    lng ans = 0;
    if (small[1] >= 2) 
        ans += small[1] * (small[1] - 1) * small[2];
    if (small[2] >= 2)
        ans += small[2] * (small[2] - 1) * small[4];
    ans += 2 * small[1] * small[2] * rest[3];
    ans += 2 * small[1] * rest[3] * small[4];
    ans += 2 * small[1] * small[4] * rest[5];
    for (lng x : {2, 4}) {
        for (auto [k, v] : rest) {
            if (!rest.contains(k + x))
                continue;

            ans += 2 * v * small[x] * rest[k + x]; 
        }
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