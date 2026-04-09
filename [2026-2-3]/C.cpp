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
    int a_sum = 0;
    vector<int> A(n);
    for (int &a : A) {
        cin >> a;
        a_sum += a;
    }

    sort(A.begin(), A.end());

    vector<int> B(n, a_sum / n);
    for (int i = n - 1; i >= n - (a_sum % n); i--) 
        B[i]++;

    lng ans = 0;
    for (int i = 0; i < n; i++)
        if (A[i] < B[i])
            ans += B[i] - A[i];

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