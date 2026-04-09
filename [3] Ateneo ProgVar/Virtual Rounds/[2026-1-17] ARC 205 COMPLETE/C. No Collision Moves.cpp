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
    // t, s, i
    deque<tuple<int, int, int>> L, R;
    indexed_set<int> S, T;
    for (int i = 1; i <= n; i++) {
        int s, t;
        cin >> s >> t;

        S.insert(s);
        if (s > t) {
            L.pb({t, s, i});
        } else {
            R.pb({t, s, i});
        }
    }

    S.insert(0);
    S.insert(1'000'000'001);
    
    sort(L.begin(), L.end());
    sort(R.begin(), R.end(), greater<tuple<int, int, int>>());

    vector<int> ans;
    for (int i = 0; i < R.size(); i++) {
        auto [t, s, j] = R[i];

        // cout << j << ": " << s << ' ' << t << endl;

        S.erase(s);
        int u = *S.find_by_order(S.order_of_key(s));
        S.insert(t);

        if (u <= t) {
            cout << "No" << endl;
            return;
        }

        ans.pb(j);
    }

    for (int s : S) 
        T.insert(-s);

    // for (int t : T)
    //     cout << t << ' ';
    // cout << endl;

    for (int i = 0; i < L.size(); i++) {
        auto [t, s, j] = L[i];

        // cout << j << ": " << s << ' ' << t << endl;
    
        T.erase(-s);
        int u = abs(*T.find_by_order(T.order_of_key(-s)));
        T.insert(-t);

        if (u >= t) {
            cout << "No" << endl;
            return;
        }

        ans.pb(j);
    }

    cout << "Yes" << endl;
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