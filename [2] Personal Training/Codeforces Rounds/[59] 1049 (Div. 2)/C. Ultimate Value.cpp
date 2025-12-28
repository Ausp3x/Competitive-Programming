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
    vector<lng> A(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> A[i];

    if (n == 2) {
        if (A[1] > A[2]) {
            cout << A[1] - A[2] << endl;
        } else {
            cout << 1 + A[2] - A[1] << endl;
        }

        return;
    }

    lng ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0)
            ans -= A[i];
        else
            ans += A[i];
    }

    lng add = (n - 1) / 2 * 2;
    vector<lng> B(n + 1, -INF64);
    for (int i = 2; i <= n; i += 2) 
        B[i] = 2 * A[i] + i - 1;
    for (int i = n - 1; i >= 1; i--) 
        B[i] = max(B[i], B[i + 1]);
    for (int i = 1; i + 1 <= n; i += 2) 
        add = max(add, B[i + 1] - 2 * A[i] - i + 1);

    vector<lng> C(n + 1, -INF64);
    for (int i = 3; i <= n; i += 2)
        C[i] = -2 * A[i] + i - 2;
    for (int i = n - 1; i >= 1; i--)
        C[i] = max(C[i], C[i + 1]);
    for (int i = 2; i + 1 <= n; i += 2)
        add = max(add, C[i + 1] + 2 * A[i] - i + 2);

    cout << ans + add << endl;

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