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
    lng n, x, y;
    cin >> n >> x >> y;
    vector<lng> A(n + 2);
    for (int i = 1; i <= n; i++)
        cin >> A[i];

    vector<lng> prf(n + 2);
    for (int i = 1; i <= n; i++)
        prf[i] = prf[i - 1] + A[i] / x * y;
    vector<lng> suf(n + 2);
    for (int i = n; i >= 1; i--) 
        suf[i] = suf[i + 1] + A[i] / x * y;

    lng ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, A[i] + prf[i - 1] + suf[i + 1]);

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