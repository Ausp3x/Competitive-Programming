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
    int a_max = 0;
    vector<int> A(n);
    for (int &a : A) {
        cin >> a;
        a_max = max(a, a_max);
    }

    sort(A.begin(), A.end());
    
    vector<pair<int, int>> D;
    for (int i = 0; i < n - 1; i++) 
        D.pb({abs(a_max - 2 * A[i]), A[i]});
    
    sort(D.begin(), D.end());

    cout << a_max << ' ' << D[0].se << endl;

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