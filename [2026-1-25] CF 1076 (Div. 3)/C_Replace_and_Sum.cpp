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
    vector<lng> A(n + 1);
    for (int i = 0; i < n; i++)
        cin >> A[i];
    vector<lng> B(n + 1);
    for (int i = 0; i < n; i++)
        cin >> B[i];

    for (int i = n - 1; i >= 0; i--)
        A[i] = max({A[i], A[i + 1], B[i]});

    for (int i = n - 1; i >= 0; i--)
        A[i] += A[i + 1];

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;

        cout << A[l] - A[r + 1] << ' ';
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