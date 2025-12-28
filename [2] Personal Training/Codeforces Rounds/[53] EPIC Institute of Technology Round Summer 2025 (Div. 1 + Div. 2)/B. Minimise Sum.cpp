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
    lng ans = 0;
    vector<int> A(n);
    for (int &a : A) {
        cin >> a;
        ans += a;
    }

    int first_non_min = n - 1;
    for (int i = 1; i < n; i++)
        if (A[i] > A[i - 1]) {
            first_non_min = i;
            break;
        }
    
    lng cur = 0;
    vector<int> M(n);
    multiset<int> S = {INF32};
    M[0] = A[0];
    cur += M[0];
    for (int i = 1; i < n; i++) {
        M[i] = min(M[i - 1], A[i]);
        if (i < first_non_min) {
            cur += M[i];
            S.insert(M[i - 1] - M[i]);
        }
    }

    ans = min(ans, cur + M[first_non_min]);    
    for (int i = first_non_min - 1; i >= 0; i--) {
        ans = min(ans, cur + min(*S.begin(), A[i + 1])); 
        cur -= M[i];
        S.erase(S.begin());    
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