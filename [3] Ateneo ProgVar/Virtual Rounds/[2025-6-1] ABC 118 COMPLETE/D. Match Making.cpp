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

vector<int> req = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<char> A(m);
    for (char &a : A)
        cin >> a;

    vector<string> memo(n + 1, "");
    auto dp = [&](int cur, auto &&dp) -> string {
        if (cur == 0 || (memo[cur] != "" && cur != 0))
            return memo[cur];

        for (char &a : A) {
            if (req[a - '0'] > cur)
                continue;

            string s = dp(cur - req[a - '0'], dp);
            if (s == "" && cur - req[a - '0'] > 0)
                continue;

            s += a;
            sort(s.begin(), s.end(), greater<char>());

            if (memo[cur].size() < s.size())
                memo[cur] = s;
            else if (memo[cur].size() == s.size() && memo[cur] < s)
                memo[cur] = s;
        }

        return memo[cur];
    };
    
    cout << dp(n, dp) << endl;

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