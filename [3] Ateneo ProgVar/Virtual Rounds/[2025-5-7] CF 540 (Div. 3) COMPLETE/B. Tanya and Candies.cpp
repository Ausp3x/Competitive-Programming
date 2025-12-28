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

    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    vector<vector<lng>> B(2, vector<lng>(n + 1));
    for (int i = 1; i <= n; i++) {
        B[i % 2][i] = A[i];
        B[0][i] += B[0][i - 1];
        B[1][i] += B[1][i - 1];
    }

    auto getSum = [&](int p, int l, int r) -> lng {
        assert(r >= l);
        return B[p][r] - B[p][l - 1];
    };

    int ans = (getSum(0, 2, n) == getSum(1, 2, n)) + (getSum(0, 1, n - 1) == getSum(1, 1, n - 1));
    for (int i = 2; i < n; i++) {
        lng L = getSum(0, 1, i - 1) + getSum(1, i + 1, n);
        lng R = getSum(1, 1, i - 1) + getSum(0, i + 1, n);
        ans += (L == R);
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