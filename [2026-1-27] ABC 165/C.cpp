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
        int n, m, q;
        cin >> n >> m >> q;
        vector<tuple<int, int, int, int>> V(q);
        for (int i = 0; i < q; i++) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;

            V[i] = {a, b, c, d};
        }

        lng ans = 0;
        vector<int> A = {1};
        auto dfs = [&](auto &&dfs) -> void {        
            if (A.size() == n + 1) {
                lng cur = 0;
                for (auto [a, b, c, d] : V) 
                    if (A[b] - A[a] == c) 
                        cur += d;

                // for (int i = 1; i <= n; i++) {
                //     cout << A[i];
                //     if (i < n)
                //         cout << ' ';
                // }
                // cout << ": " << cur << endl;
                
                ans = max(ans, cur);
                A.pop_back();
                return;
            }

            for (int i = A.back(); i <= m; i++) {
                A.pb(i);
                dfs(dfs);
            }
            A.pop_back();
        
            return;
        };

        dfs(dfs);

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