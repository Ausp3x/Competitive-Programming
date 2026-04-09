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

lng exGcd(lng a, lng b, lng &x, lng &y) {
    x = 1, y = 0;
    lng A = a, B = b, X = 0, Y = 1;
    while (B > 0) {
        lng q = A / B;
        x = exchange(X, x - q * X);
        y = exchange(Y, y - q * Y);
        A = exchange(B, A - q * B);
    }

    return A;
}

struct Dijkstra {
    int n;
    vector<bool> is_proc;
    vector<lng> dis;
    priority_queue<pair<lng, int>, vector<pair<lng, int>>, greater<pair<lng, int>>> unproc;

    Dijkstra(int n): n(n) {
        is_proc.resize(n + 1);
        dis.resize(n + 1, INF64);
    }

    void runDijkstra(const vector<int> &src, const vector<vector<int>> &adjl, lng h, const vector<lng> L, const vector<lng> S) {
        fill(is_proc.begin(), is_proc.end(), false);
        fill(dis.begin(), dis.end(), INF64);
        priority_queue<pair<lng, int>, vector<pair<lng, int>>, greater<pair<lng, int>>> empty;
        unproc.swap(empty);
        
        for (int u : src) {
            dis[u] = 0;
            unproc.push({dis[u], u});
        }
        while (!unproc.empty()) {
            int cur = unproc.top().se;
            unproc.pop();

            if (is_proc[cur]) {
                continue;
            }
            is_proc[cur] = true;
            
            lng l1 = (L[cur] + dis[cur] % h * S[cur]) % h;
            for (int nxt : adjl[cur]) {
                lng l2 = (L[nxt] + dis[cur] % h * S[nxt]) % h;
                
                lng a = ((l1 - l2) % h + h) % h;
                lng b = ((S[nxt] - S[cur]) % h + h) % h;
                lng x, y;
                lng g = exGcd(b, h, x, y);
                if (a % g != 0) 
                    continue;

                lng h2 = h / g;
                lng g2 = exGcd(b / g, h / g, x, y);
                x = (x % h2 + h2) % h2;
                lng d = (a / g % h2 * x % h2 + h2) % h2;
                // cout << cur << ' ' << nxt << ' ' << l1 << ' ' << l2 << ' ' << x << ' ' << d << endl;
                if (dis[cur] + d + 1 < dis[nxt]) {
                    dis[nxt] = dis[cur] + d + 1;
                    unproc.push({dis[nxt], nxt});
                }
            }

            // cout << cur << ' ' << dis[cur] << endl;
        };
    }
};

void solve() {
    lng n, m, h;
    cin >> n >> m >> h;
    vector<lng> L(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> L[i];
    vector<lng> S(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> S[i];
    vector<vector<int>> adjl(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adjl[u].pb(v);
        adjl[v].pb(u);
    }

    Dijkstra djk(n);

    djk.runDijkstra({1}, adjl, h, L, S);

    cout << (djk.dis[n] != INF64 ? djk.dis[n] : -1) << endl; 

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