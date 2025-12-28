// 人外有人，天外有天
// author: Ausp3x

#pragma GCC optimize("O3, fast-math")
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
    int n, m;
    cin >> n >> m;
    vector<int> A(n);
    for (int &a : A)
        cin >> a;
    vector<int> B(m);
    for (int &b : B)
        cin >> b;

    sort(B.begin(), B.end());

    vector<pair<int, int>> V = {{A[n - 1], n - 1}};
    for (int i = n - 2; i >= 0; i--)
        if (A[i] > V.back().fi)
            V.pb({A[i], i});

    reverse(V.begin(), V.end());

    while (!B.empty()) 
        if (B.back() >= V[0].fi) {
            cout << B.back() << ' ';
            B.pop_back();
        } else {
            break;
        }
    int prv_a = -1;
    for (int i = 0; i < V.size(); i++) {
        for (int j = prv_a + 1; j <= V[i].se; j++)
            cout << A[j] << ' ';

        int mn = (i == V.size() - 1 ? 0 : V[i + 1].fi);
        while (!B.empty())
            if (B.back() >= mn) {
                cout << B.back() << ' ';
                B.pop_back();
            } else {
                break;
            }

        prv_a = V[i].se;
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