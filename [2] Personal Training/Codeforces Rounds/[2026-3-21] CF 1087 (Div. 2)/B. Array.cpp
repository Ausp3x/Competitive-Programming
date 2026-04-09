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
    vector<lng> A(n);
    for (lng &a : A)
        cin >> a;

    for (int i = 0; i < n; i++) {
        vector<pair<lng, int>> E;
        int cur = 0;
        for (int j = i + 1; j < n; j++) {
            if (A[i] == A[j])
                continue;

            if (A[i] < A[j]) {
                lng b = (A[i] + A[j] - (A[i] + A[j] < 0)) / 2 + 1;
                E.pb({b, 1});
            } else {
                lng b = (A[i] + A[j] + 1 - (A[i] + A[j] + 1 < 0)) / 2;
                cur++;
                E.pb({b, -1});
            }
        }

        sort(E.begin(), E.end());

        int ans = cur;
        for (auto &[b, x] : E) {
            cur += x;
            ans = max(ans, cur);
        }

        cout << ans << ' ';
    }
    cout << endl;

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