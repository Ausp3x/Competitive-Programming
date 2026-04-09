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
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> A[i];
    
    if (n == 1) {
        cout << -1 << endl;
        return;
    }

    vector<int> B(n + 1);
    iota(B.begin(), B.end(), 0);

    for (int i = 1; i < n; i++)
        if (B[i] == A[i])
            swap(B[i], B[i + 1]);
    if (B[n] == A[n])
        swap(B[n], B[n - 1]);

    for (int i = 1; i <= n; i++)
        cout << B[i] << ' ';
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