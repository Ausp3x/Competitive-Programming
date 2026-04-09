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
    deque<char> s(n);
    for (auto &c : s)
        cin >> c;

    while (!s.empty()) {
        if (s[0] == 'R')
            s.pop_front();
        else
            break;
    }

    while (!s.empty()) {
        if (s.back() == 'W')
            s.pop_back();
        else
            break;
    }

    map<char, int> cnts;
    for (char c : s)
        cnts[c]++;

    int ans = 0;
    for (int i = 0; i < cnts['R']; i++)
        ans += (s[i] == 'W');
    
    cout << ans << endl;

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