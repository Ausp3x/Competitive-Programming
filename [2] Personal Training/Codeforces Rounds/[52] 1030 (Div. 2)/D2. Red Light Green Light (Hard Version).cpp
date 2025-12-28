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
    lng n, k;
    cin >> n >> k;
    vector<lng> P(n);
    for (lng &p : P)
        cin >> p;
    vector<lng> D(n);
    for (lng &d : D)
        cin >> d;

    auto calcX = [&](int i) -> int {
        return ((P[i] - D[i]) % k + k) % k;
    };

    auto calcY = [&](int i) -> int {
        return ((P[i] + D[i]) % k + k) % k;
    };
    
    map<int, indexed_set<int>> X, Y;
    map<int, indexed_set<lng>> Z;
    for (int i = 0; i < n; i++) {
        X[calcX(i)].insert(i);
        Y[calcY(i)].insert(i);
        Z[calcX(i)].insert(P[i]);
    }

    // approach from right (moving left) 0 -> n - 1
    vector<lng> nxt(2 * n, -1);
    for (int i = 0; i < n; i++) {
        int j = X[calcX(i)].order_of_key(i);
        if (j + 1 < X[calcX(i)].size())
            nxt[i] = *X[calcX(i)].find_by_order(j + 1) + n;
    }
    // approach from left (moving right) n - 1 -> 2n - 1
    for (int i = 0; i < n; i++) {
        int j = Y[calcY(i)].order_of_key(i);
        if (j - 1 >= 0)
            nxt[i + n] = *Y[calcY(i)].find_by_order(j - 1);
    }

    // for (int i = 0; i < 2 * n; i++) {
    //     if (nxt[i] != -1)
    //         cout << i << ' ' << nxt[i] << endl;
    // }
    // cout << endl;

    int clr = 0;
    map<int, bool> is_cyclic;
    vector<int> vst(2 * n, -1);
    for (int i = 0; i < 2 * n; i++) {
        if (vst[i] != -1)
            continue;
        vst[i] = clr;

        int j = i;
        while (nxt[j] != -1) {
            j = nxt[j];
            if (vst[j] != -1) {
                if (vst[j] == clr) {
                    is_cyclic[clr] = true;
                } else {
                    is_cyclic[clr] = is_cyclic[vst[j]];
                }
                break;
            } 
            
            vst[j] = clr;
        }

        clr++;
    }

    // for (int i = 0; i < 2 * n; i++)
    //     cout << i << ' ' << vst[i] << endl;
    // cout << endl;
    // for (auto &[k, v] : is_cyclic) 
    //     cout << k << ' ';
    // cout << endl << endl;

    int q;
    cin >> q;
    vector<lng> A(q);
    for (lng &a : A)
        cin >> a;

    for (int i = 0; i < q; i++) {
        int j = A[i] % k;
        int l = Z[j].order_of_key(A[i]);
        if (l >= X[j].size()) {
            cout << "YES" << endl;
            continue;
        }

        // cout << *X[j].find_by_order(l) + n << endl;
        if (is_cyclic[vst[*X[j].find_by_order(l) + n]]) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
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