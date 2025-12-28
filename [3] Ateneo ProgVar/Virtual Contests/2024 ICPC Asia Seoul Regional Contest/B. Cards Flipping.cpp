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
    unordered_map<int, unordered_multiset<int>> cnts;
    vector<vector<int>> V(n, vector<int>(2, -1));
    for (int i = 0; i < n; i++) {
        cin >> V[i][0];
        cnts[V[i][0]].insert(i);
    }
    for (int i = 0; i < n; i++) {
        cin >> V[i][1];
        cnts[V[i][1]].insert(i);
    }
    
    unordered_set<int> clrs;
    for (int i = 0; i < n; i++) {
        if (V[i][0] == V[i][1]) {
            cnts[V[i][0]].erase(cnts[V[i][0]].find(i));
            cnts[V[i][0]].erase(cnts[V[i][0]].find(i));
            if (cnts[V[i][0]].size() == 0)
                cnts.erase(V[i][0]);

            clrs.insert(V[i][0]);
        }
    }

    queue<int> q;
    for (auto &[c, I] : cnts)
        if (I.size() == 1) 
            q.push(c);
    
    while (!q.empty()) {
        int c = q.front();
        q.pop();

        if (cnts.find(c) == cnts.end() || clrs.find(c) != clrs.end()) {
            continue;
        }

        assert(cnts[c].size() == 1);
        
        int i = *cnts[c].begin();
        int d = (V[i][1] == c ? V[i][0] : V[i][1]);

        cnts.erase(c);
        clrs.insert(c);
        
        cnts[d].erase(cnts[d].find(i));
        if (cnts[d].size() == 0) {
            cnts.erase(d);
        } else if (cnts[d].size() == 1) {
            q.push(d);
        }
    }

    for (auto &[c, I] : cnts)
        clrs.insert(c);

    cout << clrs.size() << endl;

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