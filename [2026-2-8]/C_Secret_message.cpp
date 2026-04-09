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
    lng n, m;
    cin >> n >> m;
    vector<string> S(m);
    vector cnt(n, vector<lng>(26));
    for (auto &s : S) {
        cin >> s;

        for (int i = 0; i < n; i++)
            cnt[i][s[i] - 'a']++;
    }

    vector<lng> A;
    for (lng i = 1; i * i <= n; i++) {
        if (n % i != 0)
            continue;

        A.pb(i);
        if (i * i != n)
            A.pb(n / i);
    }

    sort(A.begin(), A.end());

    string ans = "-1";
    for (lng a : A) {
        bool chk = true;
        string cur;
        for (int i = 0; i < a; i++) {
            vector<lng> min_cnt(26, INF32);
            for (int j = i; j < n; j += a) 
                for (int k = 0; k < 26; k++)
                    min_cnt[k] = min(min_cnt[k], cnt[j][k]);
            
            lng sum = accumulate(min_cnt.begin(), min_cnt.end(), 0ll);
            if (sum > 0) {
                for (int j = 0; j < 26; j++) 
                    if (min_cnt[j] > 0) {
                        cur += char('a' + j);
                        break;
                    }
            } else {
                chk = false;
                break;
            }
        }       
        
        if (chk) {
            ans = "";
            for (int i = 0; i < n / a; i++)
                ans += cur;
            break;
        }
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