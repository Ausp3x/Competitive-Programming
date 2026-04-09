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
    vector<int> A(n);
    for (int &a : A)
        cin >> a;

    set<int> cur;
    vector<int> ans = {1}, suf;
    for (int i = 1; i <= n; i++) {
        cur.insert(A[i - 1]);

        while (!cur.empty()) {
            if (*cur.rbegin() == n - suf.size()) {
                suf.pb(*cur.rbegin());
                cur.erase(*cur.rbegin());
            } else {
                break;
            }
        }

        ans.pb(1 + i - suf.size());
    }

    for (int x : ans)
        cout << x << ' ';
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