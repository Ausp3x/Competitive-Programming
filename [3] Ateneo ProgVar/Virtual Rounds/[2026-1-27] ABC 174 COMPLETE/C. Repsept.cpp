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
    int k;
    cin >> k;

    set<int> bad = {0, 2, 4, 5, 6, 8};
    if (bad.find(k % 10) != bad.end()) {
        cout << -1 << endl;
        return;
    }

    if (k % 7 == 0)
        k /= 7;

    int rem = 9 % (9 * k);
    for (int i = 1; i <= k; i++) {
        if (rem == 0) {
            cout << i << endl;
            return;
        }
    
        rem *= 10;
        rem += 9;
        rem %= 9 * k;
    }

    cout << -1 << endl;

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