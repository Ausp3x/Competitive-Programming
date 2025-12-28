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
template<class T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n;
    cin >> n;
    vector<string> S(n);
    for (auto &s : S)
        cin >> s;

    // len, idx, differing section
    map<tuple<int, int, string>, int> cnts;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            if (S[i].size() != S[j].size())
                continue;

            int len = S[i].size();
            
            int dif_cnt = 0;
            for (int k = 0; k < len; k++)
                dif_cnt += S[i][k] != S[j][k];
            
            if (dif_cnt > 2)
                continue;

            int idx = -1;
            string s1, s2;
            for (int k = 0; k + 1 < len; k++) 
                if (S[i][k] != S[j][k] && S[i][k + 1] != S[j][k + 1]) {
                    idx = k;
                    s1 = S[i].substr(k, 2);
                    s2 = S[j].substr(k, 2);
                    break;
                }

            if (idx == -1)
                continue;

            if (s1 > s2)
                swap(s1, s2);
            cnts[{len, idx, s1 + s2}]++;
        }

    int ans = 0;
    for (auto &[k, v] : cnts) {
        if (v > 1)
            continue;

        ans++;
    }

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