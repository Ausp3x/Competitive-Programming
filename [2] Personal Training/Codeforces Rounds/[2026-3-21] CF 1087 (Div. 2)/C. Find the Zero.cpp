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

    auto query = [&](int i, int j) -> int {
        cout << "? " << i << ' ' << j << endl;
        
        int res;
        cin >> res;

        return res;
    };

    int res = query(1, 2);
    if (res == 1) {
        cout << "! 1" << endl;   
        return;
    }

    res = query(1, 3);
    if (res == 1) {
        cout << "! 1" << endl;   
        return;
    }

    res = query(2, 3);
    if (res == 1) {
        cout << "! 2" << endl;    
        return;
    }

    for (int i = 4; i < 2 * n; i += 2) {
        res = query(i, i + 1);

        if (res) {
            cout << "! " << i << endl;
            return;
        }
    }

    cout << "! " << 2 * n << endl;

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