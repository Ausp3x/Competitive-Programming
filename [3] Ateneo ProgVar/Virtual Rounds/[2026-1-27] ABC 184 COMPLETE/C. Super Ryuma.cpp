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
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    if (r1 == r2 && c1 == c2) {
        cout << 0 << endl;
        return;
    }

    if (abs(r2 - r1) == abs(c2 - c1) || abs(r2 - r1) + abs(c2 - c1) <= 3) {
        cout << 1 << endl;
        return;
    }

    if (abs(r2 - r1) % 2 == abs(c2 - c1) % 2 || abs(r2 - r1) + abs(c2 - c1) <= 6 || abs(abs(r2 - r1) - abs(c2 - c1)) <= 3) {
        cout << 2 << endl;
        return;
    }

    cout << 3 << endl;

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