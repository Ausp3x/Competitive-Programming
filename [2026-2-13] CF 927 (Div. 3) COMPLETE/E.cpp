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
    string s;
    cin >> s;

    vector<lng> A(n);
    A[0] = s[0] - '0';
    for (int i = 1; i < n; i++) 
        A[i] = A[i - 1] + (s[i] - '0');

    // for (int x : A)
    //     cout << x << ' ';
    // cout << endl;
 
    reverse(A.begin(), A.end());
    for (int i = 0; i < n; i++)
        A.pb(0);

    for (int i = 0; i < 2 * n - 1; i++) {
        A[i + 1] += A[i] / 10;
        A[i] %= 10; 
    }

    while (A.back() == 0)
        A.pop_back();

    reverse(A.begin(), A.end());

    for (int x : A)
        cout << x;
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