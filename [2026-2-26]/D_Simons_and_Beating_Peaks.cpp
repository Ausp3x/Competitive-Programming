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
    deque<int> A(n);
    for (int &a : A)
        cin >> a;
    
    vector<int> L(n, -1), R(n, -1);
    vector<int> S;
    for (int i = 0; i < n; i++) {
        int prv = -1;
        while (!S.empty()) {
            if (A[S.back()] < A[i]) {
                prv = S.back();
                S.pop_back();
            } else 
                break;
        }

        if (prv != -1) {
            L[i] = prv;
        }

        if (!S.empty()) {
            R[S.back()] = i;
        }

        S.pb(i);
    }

    auto dfs = [&](int cur, auto &&dfs) {
        if (cur == -1)
            return 0;

        return 1 + max(dfs(L[cur], dfs), dfs(R[cur], dfs));
    };

    int root = S[0];
    int mx_dep = dfs(root, dfs);
    cout << n - mx_dep << endl;

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