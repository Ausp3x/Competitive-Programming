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
    lng m;
    cin >> m;
    lng N = 0, L = 0, R = 0;
    vector<pair<lng, lng>> V;
    map<lng, bool> chk;
    vector<lng> cnts(m);
    vector<map<lng, lng>> W(m);
    for (int i = 0; i < m; i++) {
        lng n, l, r;
        cin >> n >> l >> r;
        
        N += n; L += l; R += r;
        V.pb({l, r});
        
        vector<lng> A(n), C(n);
        for (lng &a : A) 
            cin >> a;
        for (lng &c : C)
            cin >> c;
        
        for (int j = 0; j < n; j++) { 
            chk[A[j]] = true;
            cnts[i] += C[j];
            W[i][A[j]] = C[j];
        }
    }

    if (R - L > N) {
        // cout << "1: ";
        cout << 0 << endl;
        return;
    }

    for (lng i = L; i <= R; i++) 
        if (!chk[i]) {
            // cout << "2: ";
            cout << 0 << endl;
            return;
        }

    map<lng, lng> P, E;
    for (lng i = L; i <= R; i++) {
        P[i] = 0;
        E[i] = R - L;
    }
    for (int i = 0; i < m; i++)
        for (auto &[a, c] : W[i]) {
            auto [l, r] = V[i];
            E[a] -= r - l;
            if (cnts[i] - c < l) {
                P[a] += l - (cnts[i] - c);
            } else {
                E[a] += min(r, cnts[i] - c) - l;
            }
        }

    lng ans = INF64;
    for (lng i = L; i <= R; i++) {
        ans = min(ans, P[i] + max(i - L - E[i], 0ll));
    }
    cout << ans << endl;
    
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