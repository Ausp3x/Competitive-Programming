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
    vector<int> A(n);
    unordered_map<int, deque<int>> M;
    vector<deque<int>> V(30);
    for (int i = 0; i < n; i++) {
        cin >> A[i];

        M[A[i]].pb(i);
        for (int j = 0; j < 30; j++) 
            if (A[i] & (1 << j)) 
                V[j].pb(i);
    }
    for (auto &[k, v] : M) {
        v.push_front(-1);
        v.pb(n);
    }
    for (int i = 0; i < 30; i++) {
        V[i].pb(n);
    }

    auto firstLargerM = [&](int k, int i) -> int {
        int l = -1, r = M[k].size();
        while (r - l > 1) {
            int md = (l + r) / 2;
            
            if (M[k][md] < i)
                l = md;
            else 
                r = md;
        }

        return M[k][r];
    };

    lng ans = 1ll * n * (n + 1) / 2;
    for (int i = 0; i < n; i++) {
        int a_cur = A[i], L = i;
        while (true) {
            int R = n;
            for (int j = 0; j < 30; j++) {
                if (a_cur & (1 << j))
                    continue;

                while (V[j][0] < i)
                    V[j].pop_front();
                
                R = min(R, V[j][0]);
            }

            if (M.find(a_cur) != M.end()) {
                ans -= max(R - firstLargerM(a_cur, L), 0);
            }

            if (R < n) 
                a_cur |= A[R];
            L = R;

            if (R == n)
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
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}