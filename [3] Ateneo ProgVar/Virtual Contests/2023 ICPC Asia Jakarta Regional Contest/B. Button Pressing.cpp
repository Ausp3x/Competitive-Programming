// 人外有人，天外有天
// author: Ausp3x

#pragma GCC optimize("O1, O2, O3, Ofast, unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
// #define DEBUG
typedef long long    lng;
typedef __int128     lll;
template<class T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> // lower_bound and upper_bound are broken
using indexed_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n;
    cin >> n;
    vector<bool> A(n + 1);
    for (int i = 1; i <= n; i++) {
        char a;
        cin >> a;
        
        A[i] = (a - '0');
    }
    vector<bool> B(n + 1);
    for (int i = 1; i <= n; i++) {
        char b;
        cin >> b;

        B[i] = (b - '0');
    }

    vector<bool> A_prf(n + 1), B_prf(n + 1);
    for (int i = 1; i <= n; i++) {
        A_prf[i] = A_prf[i - 1] ^ A[i];
        B_prf[i] = B_prf[i - 1] ^ B[i];
    }

    int A_sum = accumulate(A_prf.begin(), A_prf.end(), 0);
    int B_sum = accumulate(B_prf.begin(), B_prf.end(), 0);
    
    cout << (A_sum == B_sum || A_sum == n + 1 - B_sum ? "YES" : "NO") << endl;

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