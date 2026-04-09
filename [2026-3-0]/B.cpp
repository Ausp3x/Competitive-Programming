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
    int n, q;
    cin >> n >> q;
    lng sum = 0;
    vector<lng> P(2), A(n);
    for (lng &a : A) {
        cin >> a;

        sum += a;
        P[a & 1]++;
    }

    while (q--) {
        lng t, x;
        cin >> t >> x;

        sum += P[t] * x;
        if (x & 1) {
            P[t ^ 1] += P[t];
            P[t] = 0;
        }

        cout << sum << endl;
    }

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