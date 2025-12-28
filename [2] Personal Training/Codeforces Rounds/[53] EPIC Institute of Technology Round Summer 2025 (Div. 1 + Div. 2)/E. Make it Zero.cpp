// 人外有人，天外有天
// author: Ausp3x
// g++ -Wall -Wextra -o <name> <name>.cpp
// <name>.exe < in > out

#pragma GCC optimize("O3, fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
// #define DEBUG
using lng = long long;
using lll = __int128;
template<typename T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> // lower_bound and upper_bound are broken
using indexed_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n;
    cin >> n;
    lng sum = 0;
    vector<lng> A(n);
    for (lng &a : A) {
        cin >> a;
        sum += a;
    }

    if (sum % 2 != 0) {
        cout << -1 << endl;
        return;
    }

    for (int i = 0; i < n; i++)
        if (A[i] > sum / 2) {
            cout << -1 << endl;
            return;
        }
    
    int idx = -1;
    lng l = 0;
    for (int i = 0; i < n; i++)
        if (l < sum / 2) {
            l += A[i];
        } else {
            idx = i - 1;
            break;
        }

    if (l == sum / 2) {
        cout << 1 << endl;
        for (lng a : A)
            cout << a << ' ';
        cout << endl;
        return;
    }
            
    l -= sum / 2;
    lng r = A[idx] - l;
    vector<lng> B(n);
    if (l < r) {
        B[idx] = l;
        for (int i = idx - 1; i >= 0; i--) {
            lng cur = min(A[i], l);
            B[i] = cur;
            l -= cur;   
        }
    } else {
        B[idx] = r;
        for (int i = idx + 1; i < n; i++) {
            lng cur = min(A[i], r);
            B[i] = cur;
            r -= cur;
        }
    }

    cout << 2 << endl;
    for (int i = 0; i < n; i++) {
        cout << B[i] << ' ';
        A[i] -= B[i];
    }
    cout << endl;
    for (lng a : A)
        cout << a << ' ';
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