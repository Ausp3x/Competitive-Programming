// 人外有人，天外有天
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
using lng = long long;
using lll = __int128;
template<typename T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    lng n;
    cin >> n;
    vector<lng> A(n);
    for (lng &a : A)
        cin >> a;

    lng l = A[0]; 
    map<lng, lng> idx;
    vector<lng> par(n);
    idx[A[0]] = 0;
    par[0] = -1;
    for (int i = 1; i < n; i++) {
        if (A[i] < l + 1 || idx.find(A[i] - 1) == idx.end()) {
            l = A[i];
            idx.clear();
            idx[A[i]] = i;
            par[i] = -1;
            continue;
        }

        if (A[i] > l + 1) {
            if (idx[A[i] - 1] < idx[A[i] - 2]) {
                l = A[i];
                idx.clear();
                idx[A[i]] = i;
                par[i] = -1;
                continue;
            }
        }

        idx[A[i]] = i;
        par[i] = idx[A[i] - 1];
    }

    // for (int x : par)
    //     cout << x << ' ';
    // cout << endl;

    lng ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (i - par[i]) * (n - i);
    }

    cout << ans << endl;
    
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