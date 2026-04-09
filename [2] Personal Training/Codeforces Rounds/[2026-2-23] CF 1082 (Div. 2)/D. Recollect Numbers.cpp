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
    int n, k;
    cin >> n >> k;
    if (k < n || k > 2 * n - 1) {
        cout << "NO" << endl;
        return;
    }
    k -= n - 1;

    if (n == 1) {
        cout << "YES" << endl;
        cout << 1 << ' ' << 1 << endl;
        return;
    }

    cout << "YES" << endl;
    cout << 1 << ' ' << k << ' ';
    for (int i = 2; i <= k; i++)
        cout << i << ' ' << i - 1 << ' ';
    for (int i = k + 1; i <= n; i++)
        cout << i << ' ' << i << ' ';
    cout << endl;

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