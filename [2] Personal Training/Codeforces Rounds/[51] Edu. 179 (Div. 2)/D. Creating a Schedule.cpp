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
    int n, m;
    cin >> n >> m;
    vector<lng> A(m);
    for (lng &a : A)
        cin >> a;

    sort(A.begin(), A.end());

    int cur = 0;
    vector<vector<lng>> ans(n, vector<lng>(6));
    for (int i = 0; i < n; i++) {
        if (i + 1 < n) {
            vector<lng> P = {A[cur], A[m - 1 - cur]};
            // cout << P[0] << ' ' << P[1] << endl;
            for (int j = 0; j < 6; j++) {
                ans[i][j] = P[j & 1];
                ans[i + 1][j] = P[!(j & 1)];
            }

            cur++;
            i++;
        } else {
            if (cur < m - 1 - cur) {
                vector<lng> P = {A[cur], A[m - 1 - cur]};
                for (int j = 0; j < 6; j++) 
                    ans[i][j] = P[j & 1];
            } else {
                for (int j = 0; j < 6; j++) 
                    ans[i][j] = A[cur];
            }

            cur++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++)
            cout << ans[i][j] << ' ';
        cout << endl;
    }

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