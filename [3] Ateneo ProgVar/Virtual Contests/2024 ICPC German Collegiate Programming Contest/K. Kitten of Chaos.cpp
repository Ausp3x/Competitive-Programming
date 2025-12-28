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
typedef long long    lng;
typedef __int128     lll;
template<class T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> // lower_bound and upper_bound are broken
using indexed_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    string s;
    cin >> s;
    string t;
    cin >> t;
    map<char, int> cnts;
    for (int i = 0; i < int(t.size()); i++)
        cnts[t[i]]++;

    if (cnts['h'] & 1) {
        reverse(s.begin(), s.end());

        map<char, char> conv = {
            {'b', 'd'},
            {'d', 'b'},
            {'p', 'q'},
            {'q', 'p'}
        };
        for (auto &c : s) 
            c = conv[c];
    } 
    
    if (cnts['v'] & 1) {
        map<char, char> conv = {
            {'b', 'p'},
            {'d', 'q'},
            {'p', 'b'},
            {'q', 'd'}
        };
        for (auto &c : s) 
            c = conv[c];
    } 
    
    if (cnts['r'] & 1) {
        reverse(s.begin(), s.end());

        map<char, char> conv = {
            {'b', 'q'},
            {'d', 'p'},
            {'p', 'd'},
            {'q', 'b'}
        };
        for (auto &c : s) 
            c = conv[c];
    }

    cout << s << endl;
    
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