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
    int sum = 0;
    vector<int> A(n), P;
    for (int i = 1; i <= n; i++) {
        cin >> A[i - 1];

        sum += __builtin_ctz(A[i - 1]);
        P.pb(__builtin_ctz(i));
    }

    sort(P.begin(), P.end());

    int ans = 0;
    while (sum < n && !P.empty()) {
        ans++;
        sum += P.back();
        P.pop_back();
    }

    cout << (sum >= n ? ans : -1) << endl;

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