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
    int n;
    cin >> n;
    int a_mn = INF32, a_mx = -INF32;
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        a_mx = max(a_mx, A[i]);
        a_mn = min(a_mn, A[i]);
    }

    vector<int> B = A;
    sort(B.begin(), B.end());

    if (B == A) {
        cout << -1 << endl;
        return;
    }

    int k = 1'000'000'000;
    for (int i = 1; i <= n; i++) 
        if (A[i] != B[i]) 
            k = min(k, max(a_mx - A[i], A[i] - a_mn));

    cout << k << endl;

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