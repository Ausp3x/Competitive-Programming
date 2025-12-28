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
    int n, M;
    cin >> n >> M;
    vector<lng> A(n);
    for (lng &a : A)
        cin >> a;

    sort(A.begin(), A.end(), greater<lng>());
    
    int l = 0, r = n + 1;
    while (r - l > 1) {
        int md = (l + r) / 2;

        lng m = 0;
        for (int i = 0; i < n; i++) {
            if (i * md >= n)
                break;
            
            for (int j = i * md; j < min((i + 1) * md, n); j++)
                m += max(A[j] - i, 0ll);
        }

        if (m >= M)
            r = md;
        else
            l = md;
    }

    if (r == n + 1) {
        cout << -1 << endl;
        return;
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