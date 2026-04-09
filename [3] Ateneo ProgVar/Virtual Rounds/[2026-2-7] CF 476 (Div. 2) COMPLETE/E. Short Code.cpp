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

struct Vertex {
    int dep = 0, prv = -1;
    vector<int> nxt;
    set<pair<int, int>> loc;

    Vertex(int dep = 0, int prv = -1): dep(dep), prv(prv) {
        nxt.resize(26);
        fill(nxt.begin(), nxt.end(), -1);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<string> S(n);
    vector<Vertex> trie(1);
    for (auto &s : S) {
        cin >> s;
        
        int cur = 0;
        for (auto ch : s) {
            int c = ch - 'a';
            if (trie[cur].nxt[c] == -1) {
                trie[cur].nxt[c] = trie.size();
                trie.pb(Vertex(trie[cur].dep + 1, cur));
            }
            cur = trie[cur].nxt[c];
        }
        trie[cur].loc.insert({trie[cur].dep, cur});
    }

    auto dfs = [&](int cur, auto &&dfs) -> void {
        int is_available = !(cur == 0 || trie[cur].loc.size() == 1);
        for (int nxt : trie[cur].nxt) {
            if (nxt == -1 || nxt == trie[cur].prv) 
                continue;

            dfs(nxt, dfs);
            
            trie[cur].loc.insert(trie[nxt].loc.begin(), trie[nxt].loc.end());
        }

        if (is_available && !trie[cur].loc.empty()) {
            trie[cur].loc.erase(prev(trie[cur].loc.end()));
            trie[cur].loc.insert({trie[cur].dep, cur});
        }
    };

    dfs(0, dfs);

    lng ans = 0;
    for (auto &[a, b] : trie[0].loc) 
        ans += a;

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