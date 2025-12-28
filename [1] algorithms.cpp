// 人外有人，天外有天
// author: Ausp3x
// g++ -Wall -Wextra -o <name> <name>.cpp
// <name>.exe < in > out

#pragma GCC optimize("O3, fast-math")
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

// TODO: Convex Hull
// TODO: Trie
// TODO: 2D Segment Tree??
// TODO: Sieve of Eratosthenes and similar Prime finders
// TODO: Ford Fulkerson + its optimization
// TODO: Kosaraju
// TODO: center of tree
// TODO: centroid of tree
// TODO: AHU algorithm
// TODO: Heavy Light Decomposition
// TODO: Li Chao Tree

// TESTED
template<typename T> 
lng kadane(const vector<T> &arr) {
    if (arr.empty()) {
        return 0;
    }

    lng max_sum = -INF64, cur_sum = -INF64;
    for (T a : arr) {
        cur_sum = max(cur_sum + a, lng(a));
        max_sum = max(max_sum, cur_sum);
    }

    return max_sum;
}



// TESTED
lng modPow(lng bse, lng exp, lng mod) {
    if (exp < 0)
        return -1;
    
    bse %= mod;
    lng res = 1;
    while (exp > 0) {
        if (exp & 1) {
            res *= bse;
            res %= mod;
        }
        
        bse *= bse;
        bse %= mod;
        exp >>= 1;
    }

    return res;
}



// TESTED
struct BridgeAlgo {
    int n, timer = 0;
    vector<bool> vst;
    vector<int> t_in, low;
    set<pair<int, int>> bridges;

    BridgeAlgo(int n, const vector<vector<int>> &adjl): n(n) {
        vst.resize(n);
        t_in.resize(n, -1);
        low.resize(n, -1);

        for (int i = 0; i < n; i++) {
            if (!vst[i]) {
                dfs(i, i, adjl);
            }
        }        
    }

    void dfs(int cur, int prv, const vector<vector<int>> &adjl) {
        vst[cur] = true;
        t_in[cur] = timer;
        low[cur] = timer;
        timer++;
        
        bool prv_skipped = false;
        for (int nxt : adjl[cur]) {
            if (nxt == prv && !prv_skipped) {
                prv_skipped = true;
                continue;
            }

            if (vst[nxt]) {
                low[cur] = min(low[cur], t_in[nxt]);
            } else {
                dfs(nxt, cur, adjl);

                low[cur] = min(low[cur], low[nxt]);
                if (low[nxt] > t_in[cur]) {
                    bridges.insert({min(cur, nxt), max(cur, nxt)});
                }
            }
        }
    }
};



// TESTED
struct ChiRemThm {
    ChiRemThm() {}

    lng extGcd(lng a, lng b, lng &x, lng &y) {
        x = 1, y = 0;
        lng x1 = 0, y1 = 1, a1 = a, b1 = b;
        while (b1 > 0) {
            lng q = a1 / b1;
            tie(x, x1) = make_tuple(x1, x - q * x1);
            tie(y, y1) = make_tuple(y1, y - q * y1);
            tie(a1, b1) = make_tuple(b1, a1 - q * b1);
        }

        return a1;
    }

    lng modInv(lng a, lng m) {
        lng x, y;
        lng g = extGcd(a, m, x, y);
        if (g != 1) {
            return -1;
        }
        
        return (x % m + m) % m;
    }

    lng runChiRemThm(const vector<lng> &arr, const vector<lng> &mods) {
        if (arr.size() != mods.size() || arr.empty()) {
            return -1;
        } 

        int n = arr.size();
        lng M = 1;
        for (int i = 0; i < n; i++) {
            M *= mods[i];
        }

        lng res = 0;
        for (int i = 0; i < n; i++) {
            lng M_i = M / mods[i];
            lng N_i = modInv(M_i, mods[i]);
            res = (res + lll(arr[i]) * M_i % M * N_i) % M;
        }

        return res;
    }
};



// TESTED
struct Dijkstra {
    int n;
    vector<bool> is_proc;
    vector<lng> dis;
    priority_queue<pair<lng, int>, vector<pair<lng, int>>, greater<pair<lng, int>>> unproc;

    Dijkstra(int n): n(n) {
        is_proc.resize(n + 1);
        dis.resize(n + 1, INF64);
    }

    void runDijkstra(const vector<int> &src, const vector<vector<int>> &adjl) {
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

            for (int nxt : adjl[cur]) {
                if (dis[cur] + 1 < dis[nxt]) {
                    dis[nxt] = dis[cur] + 1;
                    unproc.push({dis[nxt], nxt});
                }
            }
        };
    }

    void runDijkstra(const vector<int> &src, const vector<vector<pair<int, lng>>> &adjl) {
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

            for (auto [nxt, w] : adjl[cur]) {
                if (dis[cur] + w < dis[nxt]) {
                    dis[nxt] = dis[cur] + w;
                    unproc.push({dis[nxt], nxt});
                }
            }
        };
    }
};



// TESTED
struct EdmondsKarp {
    int n;
    vector<vector<bool>> adjm;
    vector<vector<int>> adjl;
    vector<vector<lng>> ocap, ncap;

    lng max_flow = 0, add_flow = 0;
    vector<int> par;
    vector<bool> in_S;
    vector<pair<int, int>> cut_set;
    
    EdmondsKarp(int n, const vector<vector<int>> &adj, const vector<vector<lng>> &cap): n(n) {
        assert(adj.size() == n + 1 && cap.size() == n + 1);
        for (int i = 0; i <= n; i++) {
            assert(cap[i].size() == n + 1);
        }

        adjm.resize(n + 1, vector<bool>(n + 1));
        ocap.resize(n + 1, vector<lng>(n + 1));
        vector<set<int>> distinct_adjl(n + 1);
        for (int u = 0; u <= n; u++) {
            for (int v : adj[u]) {
                adjm[u][v] = true;
                ocap[u][v] = cap[u][v];
                distinct_adjl[u].insert(v);
                distinct_adjl[v].insert(u);
            }
        }
        
        adjl.resize(n + 1);
        for (int u = 0; u <= n; u++) {
            for (int v : distinct_adjl[u]) {
                adjl[u].pb(v);
            }
        }

        par.resize(n + 1, -1);
        in_S.resize(n + 1);
    }

    lng augmentFlow(int s, int t) {
        fill(par.begin(), par.end(), -1);
        par[s] = s;

        queue<pair<int, lng>> q;
        q.push({s, INF64});
        while (!q.empty()) {
            auto [cur, cur_flow] = q.front();
            q.pop();

            for (int nxt : adjl[cur]) {
                if (par[nxt] == -1 && ncap[cur][nxt] > 0) {
                    par[nxt] = cur;
                    
                    lng nxt_flow = min(cur_flow, ncap[cur][nxt]);
                    if (nxt == t) {
                        return nxt_flow;
                    }
                    
                    q.push({nxt, nxt_flow});
                }
            }
        }

        return 0;
    }

    lng getMaxFlow(int s, int t) {
        assert(0 <= s && s <= n && 0 <= t && t <= n);
        max_flow = 0;
        add_flow = 0;
        ncap = ocap;

        while ((add_flow = augmentFlow(s, t)) > 0) {
            max_flow += add_flow;

            int cur = t;
            while (cur != s) {
                int prv = par[cur];
                ncap[prv][cur] -= add_flow;
                ncap[cur][prv] += add_flow;
                cur = prv;
            }
        }

        return max_flow;
    }

    void getMinCut(int s, int t) {
        getMaxFlow(s, t);
        fill(in_S.begin(), in_S.end(), false);
        in_S[s] = true;
        cut_set.clear();
        
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int nxt : adjl[cur]) {
                if (ncap[cur][nxt] > 0 && !in_S[nxt]) {
                    q.push(nxt);
                    in_S[nxt] = true;
                }
            }
        }

        for (int u = 0; u <= n; u++) {
            if (!in_S[u]) {
                continue;
            }

            for (int v : adjl[u]) {
                if (adjm[u][v] && !in_S[v]) {
                    cut_set.push_back({u, v});
                }
            }
        }
    }
};



struct Eratosthenes {
    vector<bool> is_prime;
    vector<int> primes;

};



// TESTED
struct EulerTourTree {
    int n, root;
    vector<lng> arr;
    vector<vector<int>> adjl;

    int timer = 0;
    vector<int> t_in, t_out, time_to_orig;
    vector<lng> euler;
    unique_ptr<SegTree> segt;

    EulerTourTree(int n, int root, const vector<lng> &arr, const vector<vector<int>> &adjl) : n(n), root(root), arr(arr), adjl(adjl) {
        assert(0 <= root && root < n);
        assert(arr.size() == n && adjl.size() == n);
        t_in.resize(n, -1);
        t_out.resize(n, -1);
        time_to_orig.resize(n);
        euler.resize(n);
        
        dfs(root, -1);

        segt = make_unique<SegTree>(0, n - 1, euler);
    }

    void dfs(int cur, int prv) {
        t_in[cur] = timer;
        time_to_orig[timer] = cur;
        euler[timer] = arr[cur];
        timer++;

        for (int nxt : adjl[cur]) {
            if (nxt == prv) {
                continue;
            }

            dfs(nxt, cur);
        }

        t_out[cur] = timer - 1;
    }

    void subtreeAddUpdate(int u, lng x, bool u_only = false) {
        segt->rangeAddUpdate(t_in[u], (u_only ? t_in[u] : t_out[u]), x);
    }

    void subtreeSetUpdate(int u, lng x, bool u_only = false) {
        segt->rangeSetUpdate(t_in[u], (u_only ? t_in[u] : t_out[u]), x);
    }

    pair<lng, int> subtreeMaxQuery(int u, bool u_only = false) {
        auto res = segt->rangeMaxQuery(t_in[u], (u_only ? t_in[u] : t_out[u]));
        res.se = time_to_orig[res.se];

        return res;
    }
    
    pair<lng, int> subtreeMinQuery(int u, bool u_only = false) {
        auto res = segt->rangeMinQuery(t_in[u], (u_only ? t_in[u] : t_out[u]));
        res.se = time_to_orig[res.se];

        return res;
    }

    lng subtreeSumQuery(int u, bool u_only = false) {
        return segt->rangeSumQuery(t_in[u], (u_only ? t_in[u] : t_out[u]));
    }
};



// TESTED
struct FenTree {
    int D, X, Y, Z;
    vector<lng> B1, B2, bit;

    FenTree(int x): D(1), X(x), B1(X + 1), B2(X + 1) {
        assert(x > 0);
    }
    
    FenTree(int x, int y): D(2), X(x), Y(y), bit((X + 1) * (Y + 1)) {
        assert(x > 0 && y > 0);
    }
    
    FenTree(int x, int y, int z): D(3), X(x), Y(y), Z(z), bit((X + 1) * (Y + 1) * (Z + 1)) {
        assert(x > 0 && y > 0 && z > 0);
    }

    template <typename T>
    FenTree(int x, const vector<T> &arr): FenTree(x) {
        for (int i = 0; i < x; i++) {
            rangeAddUpdate(i + 1, i + 1, arr[i]);
        }
    }

    template <typename T>
    FenTree(int x, int y, const vector<vector<T>> &arr): FenTree(x, y) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                pointAddUpdate(i + 1, j + 1, arr[i][j]);
            }
        }
    }

    template <typename T>
    FenTree(int x, int y, int z, const vector<vector<vector<T>>> &arr): FenTree(x, y, z) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                for (int k = 0; k < z; k++) {
                    pointAddUpdate(i + 1, j + 1, k + 1, arr[i][j][k]);
                }
            }
        }
    }

    // 1D methods
    inline void _add(int i_cur, lng del, vector<lng> &B) {
        for (int i = i_cur; i <= X; i += i & -i) {
            B[i] += del;
        }
    }

    inline lng _sum(int i_cur, const vector<lng> &B) const {
        lng sum = 0;
        for (int i = i_cur; i > 0; i -= i & -i) {
            sum += B[i];
        }

        return sum;
    }

    void rangeAddUpdate(int l, int r, lng del) {
        assert(D == 1);
        _add(l,     del,           B1);
        _add(r + 1, -del,          B1);
        _add(l,     del * (l - 1), B2);
        _add(r + 1, -del * r,      B2);
    }

    lng prefixSumQuery(int i) const {
        assert(D == 1);

        return _sum(i, B1) * i - _sum(i, B2);
    }

    lng rangeSumQuery(int l, int r) const {
        assert(D == 1);
        if (l > r) {
            return 0;
        }
        
        return prefixSumQuery(r) - prefixSumQuery(l - 1);
    }

    // 2D methods
    inline int getIdx(int i, int j) const {
        assert(D == 2);

        return i * (Y + 1) + j;
    }

    void pointAddUpdate(int i_cur, int j_cur, lng del) {
        assert(D == 2);
        for (int i = i_cur; i <= X; i += i & -i) {
            for (int j = j_cur; j <= Y; j += j & -j) {
                bit[getIdx(i, j)] += del;
            }
        }
    }

    lng prefixSumQuery(int i_cur, int j_cur) const {
        assert(D == 2);
        lng sum = 0;
        for (int i = i_cur; i > 0; i -= i & -i) {
            for (int j = j_cur; j > 0; j -= j & -j) {
                sum += bit[getIdx(i, j)];
            }
        }
        
        return sum;
    }

    lng rangeSumQuery(int x1, int y1, int x2, int y2) const {
        assert(D == 2);
        if (x1 > x2 || y1 > y2) {
            return 0;
        }
        
        return prefixSumQuery(x2, y2)
             - prefixSumQuery(x1 - 1, y2) - prefixSumQuery(x2, y1 - 1)
             + prefixSumQuery(x1 - 1, y1 - 1);
    }

    // 3D methods
    inline int getIdx(int i, int j, int k) const {
        assert(D == 3);

        return (i * (Y + 1) + j) * (Z + 1) + k;
    }

    void pointAddUpdate(int i_cur, int j_cur, int k_cur, lng del) {
        assert(D == 3);
        for (int i = i_cur; i <= X; i += i & -i) {
            for (int j = j_cur; j <= Y; j += j & -j) {
                for (int k = k_cur; k <= Z; k += k & -k) {
                    bit[getIdx(i, j, k)] += del;
                }
            }
        }
    }

    lng prefixSumQuery(int i_cur, int j_cur, int k_cur) const {
        assert(D == 3);
        lng sum = 0;
        for (int i = i_cur; i > 0; i -= i & -i) {
            for (int j = j_cur; j > 0; j -= j & -j) {
                for (int k = k_cur; k > 0; k -= k & -k) {
                    sum += bit[getIdx(i, j, k)];
                }
            }
        }
        
        return sum;
    }

    lng rangeSumQuery(int x1, int y1, int z1, int x2, int y2, int z2) const {
        assert(D == 3);
        if (x1 > x2 || y1 > y2 || z1 > z2) {
            return 0;
        }
        
        return prefixSumQuery(x2, y2, z2)
             - prefixSumQuery(x1 - 1, y2, z2)     - prefixSumQuery(x2, y1 - 1, z2)     - prefixSumQuery(x2, y2, z1 - 1)
             + prefixSumQuery(x1 - 1, y1 - 1, z2) + prefixSumQuery(x1 - 1, y2, z1 - 1) + prefixSumQuery(x2, y1 - 1, z1 - 1)
             - prefixSumQuery(x1 - 1, y1 - 1, z1 - 1);
    }
};



// TESTED 
struct FloydWarshall {
    int n;
    vector<vector<lng>> dis;
    
    FloydWarshall(int n, vector<vector<lng>> dis) : n(n), dis(dis) {
        assert(dis.size() == n + 1);
        for (int i = 0; i <= n; i++) {
            assert(dis[i].size() == n + 1);
        }
    }
    
    void runFloydWarshall() {
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dis[i][k] < INF64 && dis[k][j] < INF64) {
                        dis[i][j] = max(min(dis[i][j], dis[i][k] + dis[k][j]), -INF64);
                    }
                }
            }
        }
    
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    if (dis[i][k] < INF64 && dis[k][k] < 0 && dis[k][j] < INF64) {
                        dis[i][j] = -INF64;
                        break;
                    }
                }
            }
        }
    }
};



// TESTED
struct LCA {
    int n, root, l, timer = 0;
    vector<int> dep, t_in, t_out;
    vector<vector<int>> up;

    LCA(int n, int root, const vector<vector<int>> &adjl): n(n), root(root) {
        l = ceil(log2(n));
        dep.resize(n + 1);
        t_in.resize(n + 1, -1);
        t_out.resize(n + 1, -1);
        up.resize(n + 1, vector<int>(l + 1, -1));

        init(root, root, 0, adjl);
    }

    void init(int cur, int prv, int d, const vector<vector<int>> &adjl) {
        dep[cur] = d;
        t_in[cur] = timer;
        timer++;
        up[cur][0] = prv;
        for (int i = 1; i <= l; i++) {
            up[cur][i] = up[up[cur][i - 1]][i - 1];
        }

        for (int nxt : adjl[cur]) {
            if (nxt == prv) {
                continue;
            }

            init(nxt, cur, d + 1, adjl);
        }

        t_out[cur] = timer - 1;
    }

    bool isAncestor(int u, int v) const {
        return t_in[u] <= t_in[v] && t_out[v] <= t_out[u];
    }

    int getKthAncestor(int u, int k) const {
        if (k <= 0) {
            return u;
        }
        
        if (k > dep[u]) {
            return -1;
        }
        
        for (int i = l; i >= 0; i--) {
            if (k & (1 << i)) {
                u = up[u][i];
            }
        }

        return u;
    }

    int getLCA(int u, int v) const {
        if (isAncestor(u, v)) {
            return u;
        }
        
        if (isAncestor(v, u)) {
            return v;
        }

        for (int i = l; i >= 0; i--) {
            if (!isAncestor(up[u][i], v)) {
                u = up[u][i];
            }
        }

        return up[u][0];
    }
};



// TODO
struct LiChaoTree {
    using line = complex<lng>;

    vector<line> hull, vecs;

    void addLine(lng m, lng b) {
        line l = {m, b};
        while(!vecs.empty() && dotProd(vecs.back(), l - hull.back()) < 0) {
            hull.pop_back();
            vecs.pop_back();
        }

        if(!hull.empty()) {
            vecs.push_back(line(0, 1) * (l - hull.back()));
        }
        hull.push_back(l);
    }




    lng dotProd(line a, line b) {
        return (conj(a) * b).real();
    }

    lng f(line a, lng x) {
        return dotProd(a, {x, 1});
    }

};



// TESTED
struct MergeSortTree {
    int l, r;
    vector<lng> sorted;
    vector<int> l_idxs, r_idxs;
    unique_ptr<MergeSortTree> l_child, r_child;

    template<typename T> 
    MergeSortTree(int l, int r, const vector<T> &arr): l(l), r(r) {
        if (l == r) {
            sorted.pb(arr[l]);
        } else {
            sorted.resize(getRange());
            l_idxs.resize(getRange());
            r_idxs.resize(getRange());

            int m = (l + r) / 2;
            l_child = make_unique<MergeSortTree>(l, m, arr);
            r_child = make_unique<MergeSortTree>(m + 1, r, arr);
            pull();
        }
    }

    // pull states up from children
    void pull() {
        if (l_child && r_child) {
            const vector<lng> &l_sorted = l_child->sorted;
            const vector<lng> &r_sorted = r_child->sorted;
            int l_len = l_sorted.size(), r_len = r_sorted.size();

            int i = 0, j = 0, k = 0;
            while (i < l_len || j < r_len) {
                if ((i < l_len && l_sorted[i] <= r_sorted[j]) || j == r_len) {
                    sorted[k] = l_sorted[i];
                    l_idxs[k] = i;
                    r_idxs[k] = j;
                    i++;
                } else if ((j < r_len && r_sorted[j] <= l_sorted[i]) || i == l_len) {
                    sorted[k] = r_sorted[j];     
                    l_idxs[k] = i;
                    r_idxs[k] = j;
                    j++;               
                }

                k++;
            }
        }
    }

    int rangeCountLessThanQuery(int l_cur, int r_cur, lng x) const {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return 0;
        }

        if (l_cur <= l && r <= r_cur) {
            return countLessThan(x);
        }
        
        int cnt = countLessThan(x);
        int l_cnt = l_child->rangeCountLessThanQuery(l_cur, r_cur, x, (cnt < getRange() ? l_idxs[cnt] : l_child->getRange()));
        int r_cnt = r_child->rangeCountLessThanQuery(l_cur, r_cur, x, (cnt < getRange() ? r_idxs[cnt] : r_child->getRange()));
    
        return l_cnt + r_cnt;
    }

    // overloaded for internal use
    int rangeCountLessThanQuery(int l_cur, int r_cur, lng x, int cnt) const {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return 0;
        }

        if (l_cur <= l && r <= r_cur) {
            return cnt;
        }

        int l_cnt = l_child->rangeCountLessThanQuery(l_cur, r_cur, x, (cnt < getRange() ? l_idxs[cnt] : l_child->getRange()));
        int r_cnt = r_child->rangeCountLessThanQuery(l_cur, r_cur, x, (cnt < getRange() ? r_idxs[cnt] : r_child->getRange()));

        return l_cnt + r_cnt;
    }

    lng rangeMedianQuery(int l_cur, int r_cur, lng lo = 0, lng hi = 1'000'000'000'000'000'001) const {
        int req = (r_cur - l_cur + 1) / 2;
        while (hi - lo > 1) {
            lng md = (lo + hi) / 2;

            int cnt = rangeCountLessThanQuery(l_cur, r_cur, md);
            if (cnt <= req) {
                lo = md;
            } else {
                hi = md;
            }
        }
        
        return lo;
    }

    int countLessThan(lng x) const {
        return lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin();
    }

    lng getRange() const {
        return r - l + 1;
    }
};



// TESTED
struct ModFac {
    int n;
    vector<mint> fac, inv_fac;

    ModFac(int n): n(n) {
        fac.resize(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i;
        }

        inv_fac.resize(n + 1);
        inv_fac[n] = fac[n].inv();
        for (int i = n - 1; i >= 0; i--) {
            inv_fac[i] = inv_fac[i + 1] * (i + 1);
        }
    }

    mint combiNR(int x, int y) const {
        if (y > x || y < 0) {
            return mint(0);
        }

        assert(x <= n);

        return fac[x] * inv_fac[y] * inv_fac[x - y];
    }

    mint combiWR(int x, int y) const {
        if (x < 1 || y < 0) {
            return mint(0);
        }

        assert(x + y - 1 <= n);

        return fac[x + y - 1] * inv_fac[y] * inv_fac[x - 1];
    }

    mint permuNR(int x, int y) const {
        if (y > x || y < 0) {
            return mint(0);
        }

        assert(x <= n);   

        return fac[x] * inv_fac[x - y];
    }

    mint permuWR(int x, int y) const {
        if (y < 0) {
            return mint(0);
        }
        
        return mint(x).pow(y);
    }
};



// TESTED
template<lng MOD>
struct ModInt {
    lng val;

    ModInt(lng x = 0) : val(x % MOD) {
        if (val < 0) { 
            val += MOD;
        }
    }
    
    ModInt &operator++() {
        val++;
        if (val == MOD) {
            val = 0;
        }
        
        return *this;
    }

    ModInt &operator--() {
        if (val == 0) {
            val = MOD;
        }
        val--;
        
        return *this;
    }

    ModInt operator++(int) {
        ModInt res = *this;
        ++*this;
        
        return res;
    }

    ModInt operator--(int) {
        ModInt res = *this;
        --*this;

        return res;
    }

    ModInt &operator+=(const ModInt &other) {
        val += other.val;
        if (val >= MOD) {
            val -= MOD;
        }

        return *this;
    }
    
    ModInt &operator-=(const ModInt &other) {
        val -= other.val;
        if (val < 0) {
            val += MOD;
        }

        return *this;
    }
    
    ModInt &operator*=(const ModInt &other) {
        val = val * other.val % MOD;

        return *this;
    }
    
    ModInt inv() const {
        assert(val != 0);

        lng x = val, y = MOD, a = 1, b = 0, t;
        while (y > 0) {
            t = x / y;
            x -= t * y;
            a -= t * b;
            swap(x, y);
            swap(a, b);
        }

        return ModInt(a);
    }
    
    ModInt &operator/=(const ModInt &other) {
        val = val * other.inv().val % MOD;

        return *this;
    }

    ModInt pow(lng exp) const {
        assert(exp >= 0);
        
        ModInt bse = *this, res = 1;
        while (exp > 0) {
            if (exp & 1) {
                res *= bse;
            }
            
            bse *= bse;
            exp >>= 1;
        }

        return res;
    }

    ModInt operator+() const {
        return *this;
    }
    
    ModInt operator-() const {
        return ModInt() - *this;
    }

    friend ModInt operator+(const ModInt &x, const ModInt &y) {
        return ModInt(x) += y;
    }
    
    friend ModInt operator-(const ModInt &x, const ModInt &y) {
        return ModInt(x) -= y;
    }

    friend ModInt operator*(const ModInt &x, const ModInt &y) {
        return ModInt(x) *= y;
    }
    
    friend ModInt operator/(const ModInt &x, const ModInt &y) {
        return ModInt(x) /= y;
    }

    friend bool operator==(const ModInt &x, const ModInt &y) {
        return x.val == y.val;
    }

    friend bool operator!=(const ModInt &x, const ModInt &y) {
        return x.val != y.val;
    }

    friend istream &operator>>(istream &is, ModInt &x) {
        lng y;
        is >> y;
        x = ModInt(y);

        return is;
    }

    friend ostream &operator<<(ostream &os, const ModInt &x) {
        return os << x.val;
    }
};
using mint = ModInt<998'244'353>;



// TESTED
struct Random {
    mt19937    rng_int;
    mt19937_64 rng_lng; 

    Random(): 
        rng_int(random_device{}()),
        rng_lng(random_device{}()) {}

    int randInt(int l, int r) {
        return uniform_int_distribution<int>(l, r)(rng_int);
    }

    lng randLng(lng l, lng r) {
        return uniform_int_distribution<lng>(l, r)(rng_lng);
    }
};



// TESTED
struct SegTree {
    int l, r;
    lng mn = INF64, mx = -INF64, sum = 0;
    int mn_idx = -1, mx_idx = -1;
    lng add_upd = 0, set_upd = 0;
    bool set_flag = false;
    unique_ptr<SegTree> l_child, r_child;

    template<typename T> 
    SegTree(int l, int r, const vector<T> &arr): l(l), r(r) {
        if (l == r) {
            assert(-INF64 <= arr[l] && arr[l] <= INF64);
            mn = mx = sum = arr[l];
            mn_idx = mx_idx = l;
        } else {
            int m = (l + r) / 2;
            l_child = make_unique<SegTree>(l, m, arr);
            r_child = make_unique<SegTree>(m + 1, r, arr);
            pull();
        }
    }

    // push updates down to children
    void push() {
        if (l_child && r_child) {
            if (set_flag) {
                l_child->add_upd = 0;
                l_child->set_upd = set_upd;
                l_child->set_flag = true;
                l_child->mn = l_child->mx = set_upd;
                l_child->sum = l_child->getRange() * set_upd;
                l_child->mn_idx = l_child->mx_idx = l_child->l;
                
                r_child->add_upd = 0;
                r_child->set_upd = set_upd;
                r_child->set_flag = true;
                r_child->mn = r_child->mx = set_upd;
                r_child->sum = r_child->getRange() * set_upd;
                r_child->mn_idx = r_child->mx_idx = r_child->l;
                
                set_upd = 0;
                set_flag = false;
            }

            if (add_upd != 0) {
                l_child->add_upd += add_upd;
                l_child->mn += add_upd;
                l_child->mx += add_upd;
                l_child->sum += l_child->getRange() * add_upd;
                
                r_child->add_upd += add_upd;
                r_child->mn += add_upd;
                r_child->mx += add_upd;
                r_child->sum += r_child->getRange() * add_upd;

                add_upd = 0;
            }
        }
    }

    // pull states up from children
    void pull() {
        assert(add_upd == 0 && set_upd == 0 && !set_flag);
        if (l_child && r_child) {
            if (l_child->mn <= r_child->mn) {
                mn = l_child->mn;
                mn_idx = l_child->mn_idx;
            } else {
                mn = r_child->mn;
                mn_idx = r_child->mn_idx;
            }

            if (l_child->mx >= r_child->mx) {
                mx = l_child->mx;
                mx_idx = l_child->mx_idx;
            } else {
                mx = r_child->mx;
                mx_idx = r_child->mx_idx;
            }

            sum = l_child->sum + r_child->sum;
        }
    }

    void rangeAddUpdate(int l_cur, int r_cur, lng x) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return;
        }
        
        if (l_cur <= l && r <= r_cur) {
            if (set_flag) {
                set_upd += x;
            } else { 
                add_upd += x; 
            }
            mn += x;
            mx += x;
            sum += getRange() * x;            
            return;
        }
        
        push();
        l_child->rangeAddUpdate(l_cur, r_cur, x);
        r_child->rangeAddUpdate(l_cur, r_cur, x);
        pull();
    }

    void rangeSetUpdate(int l_cur, int r_cur, lng x) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return;
        }
        
        if (l_cur <= l && r <= r_cur) {
            add_upd = 0;
            set_upd = x;
            set_flag = true;
            mn = mx = x;
            sum = getRange() * x;
            mn_idx = mx_idx = l;
            return;
        }
        
        push();
        l_child->rangeSetUpdate(l_cur, r_cur, x);
        r_child->rangeSetUpdate(l_cur, r_cur, x);
        pull();
    }

    pair<lng, int> rangeMaxQuery(int l_cur, int r_cur) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return {-INF64, -1};
        }

        if (l_cur <= l && r <= r_cur) {
            return {mx, mx_idx};
        }
        
        push();
        auto l_res = l_child->rangeMaxQuery(l_cur, r_cur);
        auto r_res = r_child->rangeMaxQuery(l_cur, r_cur);
        if (l_res.fi >= r_res.fi) {
            return l_res;
        } else {
            return r_res;
        }
    }

    pair<lng, int> rangeMinQuery(int l_cur, int r_cur) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return {INF64, -1};
        }

        if (l_cur <= l && r <= r_cur) {
            return {mn, mn_idx};
        }
        
        push();
        auto l_res = l_child->rangeMinQuery(l_cur, r_cur);
        auto r_res = r_child->rangeMinQuery(l_cur, r_cur);
        if (l_res.fi <= r_res.fi) {
            return l_res;
        } else {
            return r_res;
        }
    }

    lng rangeSumQuery(int l_cur, int r_cur) {
        if (l_cur > r_cur || (r < l_cur || r_cur < l)) {
            return 0;
        } 
        
        if (l_cur <= l && r <= r_cur) {
            return sum;
        } 
        
        push();

        return l_child->rangeSumQuery(l_cur, r_cur) + r_child->rangeSumQuery(l_cur, r_cur);
    }

    lng getRange() const {
        return r - l + 1;
    }
};



// TESTED
struct UnionFind {
    int n;
    vector<int> par, dis, node_cnts, edge_cnts;

    UnionFind(int n): n(n) {
        par.resize(n + 1);
        iota(par.begin(), par.end(), 0);
        dis.resize(n + 1);
        node_cnts.resize(n + 1, 1);
        edge_cnts.resize(n + 1);
    }

    int findSet(int u) {
        if (u != par[u]) {
            int root = findSet(par[u]);
            dis[u] += dis[par[u]];
            par[u] = root;
        }

        return par[u];
    }

    int getDistanceToSet(int u) {
        findSet(u);
        
        return dis[u];
    }

    bool isSameSet(int u, int v) {
        return findSet(u) == findSet(v);
    }

    void uniteSets(int u, int v) {
        u = findSet(u);
        v = findSet(v);
        if (u == v) {
            edge_cnts[u]++;
            return;
        }

        if (node_cnts[u] < node_cnts[v]) {
            swap(u, v);
        }

        par[v] = u;
        dis[v] = 1;
        node_cnts[u] += node_cnts[v];
        edge_cnts[u] += edge_cnts[v] + 1;
    }
};
