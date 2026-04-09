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
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> A[i];
        
    deque<int> O;
    for (int i = 1; i <= x; i++)
        O.pb(A[i]);
    for (int i = y + 1; i <= n; i++)
        O.pb(A[i]);
    
    int i_mn = INF32;
    deque<int> I;
    for (int i = x + 1; i <= y; i++) {
        i_mn = min(i_mn, A[i]);
        I.pb(A[i]);
    }

    if (I.empty()) {
        for (int x : O)
            cout << x << ' ';
        cout << endl;
        return;
    }

    while (I[0] != i_mn) {
        I.pb(I[0]);
        I.pop_front();
    }

    while (!O.empty()) {
        if (O[0] < I[0]) {
            cout << O[0] << ' ';
            O.pop_front();
        } else
            break;
    }
    for (int x : I)
        cout << x << ' ';
    for (int x : O)
        cout << x << ' ';
    cout << endl;

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