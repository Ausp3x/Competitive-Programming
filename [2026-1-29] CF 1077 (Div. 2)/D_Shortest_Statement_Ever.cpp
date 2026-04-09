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
    lng x, y;
    cin >> x >> y;

    if (x == 0 || y == 0) {
        cout << x << ' ' << y << endl;
        return;
    }

    auto hasBit = [&](int x, int i) -> bool {
        return x & (1 << i);
    };

    auto getVal = [&](int a, int b) -> int {
        return abs(x - a) + abs(y - b);
    };

    int ans = INF32;
    int a_ans = -1, b_ans = -1;

    int a = 0, b = 0;
    vector<bool> used(31);
    for (int i = 30; i >= 0; i--) {
        if (!hasBit(x, i) && !hasBit(y, i)) {
            int x_rem = x % (1 << i);
            int y_rem = y % (1 << i);

            if (x_rem > y_rem) {
                a += 1 << i;
                b += y_rem;
                
                if (getVal(a, b) < ans) { 
                    ans = getVal(a, b);
                    a_ans = a; b_ans = b;
                    // cout << 0 << ' ' << a << ' ' << b << endl;
                }

                a -= 1 << i;
                b -= y_rem;
            } else {
                a += x_rem;
                b += 1 << i;
                
                if (getVal(a, b) < ans) { 
                    ans = getVal(a, b);
                    a_ans = a; b_ans = b;
                    // cout << 0 << ' ' << a << ' ' << b << endl;
                }

                a -= x_rem;
                b -= 1 << i;
            }
            continue;
        }

        if (hasBit(x, i) && hasBit(y, i)) {
            if (used[i + 1]) {
                a += 1 << i;
                b += (1 << i) - 1;

                if (getVal(a, b) < ans) { 
                    ans = getVal(a, b);
                    a_ans = a; b_ans = b;
                    // cout << 1 << ' ' << a << ' ' << b << endl;
                }

                a -= 1 << i;
                b -= (1 << i) - 1;
                break;
            }

            int x_rem = x % (1 << (i + 1));
            int y_rem = y % (1 << (i + 1));

            a += 1 << (i + 1);
            b += y_rem;

            if (getVal(a, b) < ans) { 
                ans = getVal(a, b);
                a_ans = a; b_ans = b;
                // cout << 1 << ' ' << a << ' ' << b << endl;
            }

            a -= 1 << (i + 1);
            b -= y_rem;


            a += x_rem;
            b += 1 << (i + 1);

            if (getVal(a, b) < ans) { 
                ans = getVal(a, b);
                a_ans = a; b_ans = b;
                // cout << 1 << ' ' << a << ' ' << b << endl;
            }

            a -= x_rem;
            b -= 1 << (i + 1);


            a += 1 << i;
            b += (1 << i) - 1;

            if (getVal(a, b) < ans) { 
                ans = getVal(a, b);
                a_ans = a; b_ans = b;
                // cout << 1 << ' ' << a << ' ' << b << endl;
            }

            a -= 1 << i;
            b -= (1 << i) - 1;
            break;
        } 
        
        if (hasBit(x, i)) {
            a += 1 << i;
            used[i] = true;
        } else if (hasBit(y, i)) {
            b += 1 << i;
            used[i] = true;
        } 

        if (getVal(a, b) < ans) { 
            ans = getVal(a, b);
            a_ans = a; b_ans = b;
            // cout << 2 << ' ' << a << ' ' << b << endl;
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