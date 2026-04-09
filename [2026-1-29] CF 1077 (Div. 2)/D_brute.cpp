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

/*
def generator(t):
    return f'1\n{random.randint(1, 1023)} {random.randint(1, 1023)}'
*/

void solve() {
    int x, y;
    cin >> x >> y;

    auto hasBit = [&](int x, int i) -> bool {
        return x & (1 << i);
    };

    auto getVal = [&](int a, int b) -> int {
        return abs(x - a) + abs(y - b);
    };

    int ans = INF32;
    int a_ans = -1, b_ans = -1;
    for (int a = 0; a < (1 << 12); a++) {   
        for (int b = 0; b < (1 << 12); b++) {
            if ((a & b) != 0)
                continue;

            if (getVal(a, b) < ans) { 
                ans = getVal(a, b);
                a_ans = a; b_ans = b;
            }
        }
    }

    cout << a_ans << ' ' << b_ans << endl;
    // cout << ans << endl;

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