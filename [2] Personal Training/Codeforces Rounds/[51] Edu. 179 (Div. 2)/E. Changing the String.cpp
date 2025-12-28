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
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    map<string, indexed_set<int>> M;
    for (int i = 0; i < q; i++) {
        string c = "XX";
        cin >> c[0] >> c[1];
        
        M[c].insert(i);
    }

    for (auto &c : s) {
        if (c == 'a') 
            continue;

        if (c == 'b') {
            if (M["ba"].size() > 0) {
                c = 'a';
                M["ba"].erase(M["ba"].find_by_order(0));
            } else if (M["bc"].size() > 0 && M["ca"].size() > 0 && M["ca"].order_of_key(*M["bc"].find_by_order(0)) < M["ca"].size()) {
                int l = *M["bc"].find_by_order(0);
                int r = *M["ca"].find_by_order(M["ca"].order_of_key(l));

                c = 'a';
                M["bc"].erase(l);
                M["ca"].erase(r);
            }
            continue;
        }

        if (M["ca"].size() > 0) {
            c = 'a';
            M["ca"].erase(M["ca"].find_by_order(0));
        } else if (M["cb"].size() > 0 && M["ba"].size() > 0 && M["ba"].order_of_key(*M["cb"].find_by_order(0)) < M["ba"].size()) {
            int l = *M["cb"].find_by_order(0);
            int r = *M["ba"].find_by_order(M["ba"].order_of_key(l));

            c = 'a';
            M["cb"].erase(l);
            M["ba"].erase(r);
        } else if (M["cb"].size() > 0) {
            c = 'b';
            M["cb"].erase(M["cb"].find_by_order(0));
        }
    }

    cout << s << endl;

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