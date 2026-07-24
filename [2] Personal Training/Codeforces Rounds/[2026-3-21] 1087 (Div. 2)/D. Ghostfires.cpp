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
    int r, g, b;
    cin >> r >> g >> b;

    string to_c = "RGB";

    vector<pair<int, int>> I = {{r, 0}, {g, 1}, {b, 2}};
    sort(I.begin(), I.end(), greater<pair<int, int>>());
 
    bool chk = false, par = 0;
    string ans;
    while (true) {
        if (chk) {
            if (I[par].fi == 0) {
                break;
            }

            ans += to_c[I[par].se];
            I[par].fi--;
            chk = false;
        } else {
            if (I[par].fi == 0 && I[2].fi == 0)
                break;

            if (I[2].fi > I[par].fi) {
                swap(I[par], I[2]);
                chk = true;
            }

            ans += to_c[I[par].se];
            I[par].fi--;
        }

        par ^= 1;
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