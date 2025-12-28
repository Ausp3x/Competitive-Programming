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

int N = 30;
vector<int> F(N + 1);

void solve() {
    int n;
    cin >> n;
    map<int, int> cnts, cur_buck;
    vector<int> ttls(N + 1);
    vector<set<pair<int, int>>> buckets(N + 1);
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;

        if (cur_buck.find(s) == cur_buck.end()) {
            for (int j = 2; j <= N; j++) {
                if (buckets[j].size() < F[j]) {
                    cnts[s] = 1;
                    cur_buck[s] = j;
                    ttls[j]++;
                    buckets[j].insert({1, s});
                    break;
                }
            }

            lng ans = 0;
            for (int j = 2; j <= N; j++) {
                ans += j * ttls[j];
            }

            // cout << ans << endl << endl;
            cout << ans << ' ';
                
            continue;
        }
        
        ttls[cur_buck[s]] -= cnts[s];
        buckets[cur_buck[s]].erase({cnts[s], s});

        cnts[s]++;

        for (int j = 2; j <= N; j++) {
            if (buckets[j - 1].size() >= F[j - 1] || buckets[j].empty())
                continue;

            auto [t_cnt, t] = *buckets[j].rbegin();
            
            ttls[j] -= t_cnt;
            buckets[j].erase({t_cnt, t});
            
            cur_buck[t] = j - 1;
            ttls[j - 1] += t_cnt;
            buckets[j - 1].insert({t_cnt, t});
        }

        for (int j = 2; j <= N; j++)
            if (buckets[j].empty() || buckets[j].begin()->fi <= cnts[s]) {                
                cur_buck[s] = j;
                ttls[j] += cnts[s];
                buckets[j].insert({cnts[s], s});
                break;
            }
        
        for (int j = 2; j < N; j++) {
            if (buckets[j].size() <= F[j])
                continue;

            auto [t_cnt, t] = *buckets[j].begin();
            
            ttls[j] -= t_cnt;
            buckets[j].erase({t_cnt, t});
            
            cur_buck[t] = j + 1;
            ttls[j + 1] += t_cnt;
            buckets[j + 1].insert({t_cnt, t});
        }

        lng ans = 0;
        for (int j = 2; j <= N; j++) {
            ans += j * ttls[j];
        }

        // cout << ans << endl << endl;
        cout << ans << ' ';
    }
    cout << endl;
    
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    F[0] = 0;
    F[1] = 0;
    F[2] = 1;
    F[3] = 1;
    for (int i = 4; i <= N; i++)
        F[i] = F[i - 1] + F[i - 2];
    // for (int i = 1; i <= N; i++)
    //     F[i] += F[i - 1];

    // for (int i = 0; i <= N; i++)
    //     cout << F[i] << ' ';
    // cout << endl;
    
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}