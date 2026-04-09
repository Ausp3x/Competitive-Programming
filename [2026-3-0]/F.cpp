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
    vector<int> A(n), I(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        I[A[i]] = i;
    }

    int l = INF32, r = -INF32;
    lng ans = 0;
    for (int a = 0; a < (n + 1) / 2; a++) {
        l = min(l, I[a]);
        r = max(r, I[a]);

        int L = max(r - 2 * a, 0);
        int R = min(n - 2 * a - 1, l);
        ans += max(R - L + 1, 0);

        // cout << 2 * a + 1 << ": " << l << ' ' << r << ' ' << L << ' ' << R << endl;

        if (2 * a + 2 > n)
            break;

        L = max(r - 2 * a - 1, 0);
        R = min(n - 2 * a - 2, l);
        ans += max(R - L + 1, 0);

        // cout << 2 * a + 2 << ": " << l << ' ' << r << ' ' << L << ' ' << R << endl;
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