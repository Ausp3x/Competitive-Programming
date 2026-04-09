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
    deque<lng> D(2 * n);
    for (lng &d : D)
        cin >> d;

    sort(D.begin(), D.end(), greater<lng>());

    int cnt = 2 * n;
    lng sum = 0;
    vector<lng> A;
    while (!D.empty()) {
        if (D[0] != D[1] || (D[0] - sum) % cnt != 0) {
            cout << "NO" << endl;
            return;
        } 

        lng cur = (D[0] - sum) / cnt;
        if (!A.empty())
            if (cur >= A.back() || cur <= 0) {
                cout << "NO" << endl;
                return;
            }

        cnt -= 2;
        sum += 2 * cur;
        A.pb(cur);
        D.pop_front();
        D.pop_front();
    }

    cout << "YES" << endl;
    // for (lng a : A)
    //     cout << a << ' ';
    // cout << endl;

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