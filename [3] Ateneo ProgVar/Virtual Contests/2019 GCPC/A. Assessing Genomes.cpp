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

int getScore(string s) {
    int n = s.size();
    for (int len = 1; len < n; len++) {
        if (n % len != 0)
            continue;
        
        for (int i = 0; i + len - 1 < n; i++) {
            string sub = s.substr(i, len), t;
            for (int j = 0; j < n / len; j++)
                t += sub;

            if (t == s) 
                return len;
        }
    }

    return n;
}

void solve() {
    int n;
    cin >> n;
    vector<int> V(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        V[i] = getScore(s);
        // cout << V[i] << ' ';
    }
    // cout << endl;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        A[i] = getScore(s);
        // cout << A[i] << ' ';
    }
    // cout << endl;

    sort(V.begin(), V.end());
    sort(A.begin(), A.end());

    int ans = 0;
    for (int i = 0; i < n; i++) 
        ans += (A[i] - V[i]) * (A[i] - V[i]);
    
    cout << ans << endl;

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