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
    int n, m;
    cin >> n >> m;
    int len = 0;
    vector<bool> in_A(n + m + 1, false);
    vector<int> A(n);
    for (int &a : A) {
        cin >> a;
        
        if (!in_A[a]) {
            in_A[a] = true;
            len++;
        }
    }
    vector<int> B(m);
    for (int &b : B)
        cin >> b;

    vector<int> divs(n + m + 1);
    for (int i = 1; i <= n + m; i++) 
        if (in_A[i]) 
            for (int j = i; j <= n + m; j += i) 
                divs[j]++;

    vector<int> cnts(3);
    for (int b : B) {
        if (divs[b] == len) {
            cnts[1]++;
        } else if (divs[b] == 0) {
            cnts[2]++;
        } else {
            cnts[0]++;
        }
    }

    int ali = (cnts[0] + 1) / 2 + cnts[1];
    int bob = cnts[0] / 2 + cnts[2];

    cout << (ali > bob ? "Alice" : "Bob") << endl;

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