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
    lng ans = 0;
    vector<tuple<lng, lng, lng>> A(n);
    for (auto &[s, l, r] : A) {
        cin >> l >> r;
        s = l + r;

        ans += r - l;
    }

    sort(A.begin(), A.end());

    lng L = 0, R = 0;
    for (int i = 0; i < n / 2; i++) 
        L += get<1>(A[i]);
    for (int i = n - n / 2; i < n; i++)
        R += get<2>(A[i]);

    if (n % 2 == 0) {
        ans += R - L;
        cout << ans << endl;
        return;
    }

    lng cur = R - L;
    for (int i = 0; i < n / 2; i++) 
        cur = max(cur, R - L + get<1>(A[i]) - get<1>(A[n / 2]));
    for (int i = n - n / 2; i < n; i++) 
        cur = max(cur, R - L - get<2>(A[i]) + get<2>(A[n / 2]));

    cout << ans + cur << endl;

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