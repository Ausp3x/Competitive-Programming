// 人外有人，天外有天
// author: Ausp3x

#pragma GCC optimize("O1, O2, O3, Ofast, unroll-loops")
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

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, q;
    cin >> n >> q;
    int grp = 0;
    vector<int> R(n + 1), row_grp(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> R[i];

        if (R[i] % 2 != R[i - 1] % 2)
            grp++;
        row_grp[i] = grp;
    }
    grp = 0;
    vector<int> C(n + 1), col_grp(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> C[i];

        if (C[i] % 2 != C[i - 1] % 2)
            grp++;
        col_grp[i] = grp;
    }

    while (q--) {
        int ra, ca, rb, cb;
        cin >> ra >> ca >> rb >> cb;

        cout << (row_grp[ra] == row_grp[rb] && col_grp[ca] == col_grp[cb] ? "YES" : "NO") << endl;
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