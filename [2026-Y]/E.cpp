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
    int n, x, y;
    cin >> n >> x >> y;
    
    auto query = [&](const vector<int> &A) -> int {
        cout << "? " << A.size() << ' ';
        for (int a : A)
            cout << a << ' ';
        cout << endl;
    
        int res;
        cin >> res;
    
        if (res == 0 || res == x) {
            return 0;
        }
    
        return 1;
    };
    
    int k = __lg(n - 1);
    vector<bool> D(k + 1);
    for (int i = 0; i <= k; i++) {
        vector<int> A;
        for (int j = 0; j < n; j++) {
            if (j & (1 << i))
                continue;
    
            A.pb(j + 1);
        }
        
        D[i] = query(A);
    }
    
    bool first_d = true;
    int l = 0, r = 0;
    vector<int> same;
    for (int i = k; i >= 0; i--) {
        if (!D[i] && first_d) {
            same.pb(i);
            continue;
        }
        
        if (D[i] && first_d) {
            reverse(same.begin(), same.end());

            while (!same.empty()) {
                vector<int> A;
                for (int j = 0; j < (1 << i); j++)
                    for (int msk = 0; msk < (1 << same.size() - 1); msk++)
                        A.pb(l + (msk << i + 1) + j + 1);

                int res = query(A);

                if (res == 0) {
                    l += 1 << same.back();
                    r += 1 << same.back();    
                }

                same.pop_back();
            }

            r += 1 << i;
            first_d = false;
            continue;
        }
    
        vector<int> A;
        for (int j = 0; j < (1 << i); j++)
            A.pb(l + j + 1);
    
        int res = query(A);
    
        if (!D[i]) {
            if (res == 0) {
                l += 1 << i;
                r += 1 << i;
            }
            continue;
        }
    
        if (res == 0) {
            l += 1 << i;
        } else {
            r += 1 << i;
        }
    }
    
    cout << "! " << l + 1 << ' ' << r + 1 << endl;
    
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