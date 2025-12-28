// 人外有人，天外有天
// author: Ausp3x
// g++ -Wall -Wextra -o <name> <name>.cpp
// <name>.exe < in > out

#pragma GCC optimize("O3, fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
// #define DEBUG
using lng = long long;
using lll = __int128;
template<typename T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> // lower_bound and upper_bound are broken
using indexed_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

vector<lng> pow10(19, 1);

void solve() {
    lng P;
    cin >> P;
    
    lng Q = P;
    set<int> av = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<bool> usedP(10);
    while (Q > 0) {
        if (av.contains(Q % 10))
            av.erase(Q % 10);
        usedP[Q % 10] = true;
        Q /= 10;
    }

    // count the number of pairs x, y s.t.
    // x < y
    // x + y = P
    // |D(x)| + |D(y)| + |D(P)| = |D(x) + D(y) + D(P)|

    vector<bool> usedX(10);

    auto check = [&](int max_pos, int pos, lng y) -> bool {
        // cout << y << endl;

        for (int i = 18; i >= pos; i--) {
            if (y / pow10[i] == 0)
                continue;
            
            if (i == pos && pos != 0)
                continue;

            // cout << y / pow10[i] % 10 << ' ';
            
            if (usedP[y / pow10[i] % 10] || usedX[y / pow10[i] % 10]) {
                // cout << endl;
                return false;
            }
        }
        // cout << endl;
        
        return true;
    };

    int cnt = 0;
    vector<pair<lng, lng>> ans;

    auto count = [&](int max_pos, int pos, lng x, set<int> avX, auto &&count) -> void {
        if (pos == -1) {
            cnt++;
            if (ans.size() < 5000)
                ans.pb({x, P - x});

            return;
        }

        for (int i : avX) {
            if (pos == max_pos && i == 0)
                continue;
            
            lng new_x = x + i * pow10[pos];
            if (2 * new_x >= P)
                continue;
            lng y = P - new_x;

            int orig = usedX[i];
            usedX[i] = true;
            // cout << new_x << ' ';
            if (!check(max_pos, pos, y)) {
                usedX[i] = orig;
                continue;
            }

            set<int> new_avX = avX;
            if (pos == max_pos) {
                for (int i = 18; i > pos; i--) {
                    if (y / pow10[i] == 0)
                        continue;
                    
                    if (new_avX.contains(y / pow10[i] % 10))
                        new_avX.erase(y / pow10[i] % 10);
                }
            } else if (pos + 1 <= 18) {
                if (new_avX.contains(y / pow10[pos + 1] % 10))
                    new_avX.erase(y / pow10[pos + 1] % 10);
            }

            count(max_pos, pos - 1, new_x, new_avX, count);

            usedX[i] = orig;
        }
        
        return;
    };

    for (int i = 0; i <= 17; i++) {
        count(i, i, 0, av, count);
    }

    cout << cnt << endl;
    for (auto &[x, y] : ans)
        cout << x << ' ' << y << endl;

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 1; i < 19; i++) 
        pow10[i] = pow10[i - 1] * 10;

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}