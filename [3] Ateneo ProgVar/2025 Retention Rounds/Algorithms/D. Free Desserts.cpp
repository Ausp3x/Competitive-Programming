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

vector<int> pow3(11, 1);
vector<lng> pow10(19, 1);

void solve() {
    lng P;
    cin >> P;
    int lenP = int(log10(P)) + 1;

    set<int> avX = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < lenP; i++) {
        int dp = P / pow10[i] % 10;
        if (avX.contains(dp));
            avX.erase(dp);
    }

    auto isValid = [&](int dx, int dy, int &msk) -> bool {
        if (msk / pow3[dx] % 3 == 2)
            return false;
        
        if (msk / pow3[dy] % 3 == 1)
            return false;

        if (msk / pow3[dx] % 3 == 0)
            msk += pow3[dx];
        if (msk / pow3[dy] % 3 == 0)
            msk += 2 * pow3[dy];
        
        return true;
    };

    vector<vector<vector<lng>>> memo(lenP + 1, vector<vector<lng>>(2, vector<lng>(pow3[10], -1)));
    memo[0][0][0] = 1;
    for (int pos = 0; pos < lenP; pos++) 
        for (int car : {0, 1}) 
            for (int msk = 0; msk < pow3[10]; msk++) {
                if (memo[pos][car][msk] == -1)
                    continue;

                for (int dx : avX) {
                    int dp = P / pow10[pos] % 10 - car;
                    if (dp < 0) dp += 10;
                    
                    if (dp - dx >= 0) {
                        int dy = dp - dx;
                        int new_msk = msk;
                        if (isValid(dx, dy, new_msk)) {
                            if (memo[pos + 1][0][new_msk] == -1)
                                memo[pos + 1][0][new_msk] = 0;
                            memo[pos + 1][0][new_msk] += memo[pos][car][msk];
                        }
                    }

                    if (dp + 10 - dx < 10) {
                        int dy = dp + 10 - dx;
                        int new_msk = msk;
                        if (isValid(dx, dy, new_msk)) {
                            if (memo[pos + 1][1][new_msk] == -1)
                                memo[pos + 1][1][new_msk] = 0;
                            memo[pos + 1][1][new_msk] += memo[pos][car][msk];
                        }
                    }
                }
            }

    lng ans = 0;
    for (int car : {0, 1})
        for (int msk = 1; msk < pow3[10]; msk++) {
            if (memo[lenP][car][msk] == -1)
                continue;

            ans += memo[lenP][car][msk];
        }

    cout << ans << endl;

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 1; i < 11; i++)
        pow3[i] = pow3[i - 1] * 3;

    for (int i = 1; i < 19; i++)
        pow10[i] = pow10[i - 1] * 10;

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}