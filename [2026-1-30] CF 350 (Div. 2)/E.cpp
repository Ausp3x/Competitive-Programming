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
    int n, m, p;
    cin >> n >> m >> p;
    p--;
    string s;
    cin >> s;
    string op;
    cin >> op;

    map<int, int> M;
    stack<pair<char, int>> S;
    queue<pair<char, int>> Q;
    for (int i = 0; i < n; i++)
        Q.push({s[i], i});
    while (!Q.empty()) {
        auto [c, i] = Q.front();
        Q.pop();

        if (c == '(') {
            S.push({c, i});
        } else {
            auto [c2, i2] = S.top();
            S.pop();

            M[i2] = i;
            M[i] = i2;
        }
    }

    indexed_set<int> is;
    is.insert(-1);
    for (int i = 0; i < n; i++) 
        is.insert(i);
    is.insert(n);
    for (auto c : op) {
        if (c == 'L') {
            p = *is.find_by_order(is.order_of_key(p) - 1);
        } else if (c == 'R') {
            p = *is.find_by_order(is.order_of_key(p) + 1);
        } else {
            int l = min(p, M[p]);
            int r = max(p, M[p]);
            while (*is.find_by_order(is.order_of_key(l)) <= r) {
                is.erase(is.find_by_order(is.order_of_key(l)));
            }

            p = *is.find_by_order(is.order_of_key(p));
            if (p == n) 
                p = *is.find_by_order(is.order_of_key(p) - 1);
        }
    }

    for (int x : is) {
        if (x == -1 || x == n)
            continue;

        cout << s[x];
    }
    cout << endl;

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