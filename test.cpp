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

// T: O(1), M: O(1)
template<lng MOD>
struct ModInt {
    int n;

    ModInt(lng N = 0): n(N % MOD) {
        if (n < 0) { 
            n += MOD;}
    }

    explicit operator lng() const {
        return n;
    }
    
    ModInt &operator++() {
        n++;
        if (n == MOD) {
            n = 0;}
        
        return *this;
    }

    ModInt &operator--() {
        if (n == 0) {
            n = MOD;}
        n--;
        
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

    ModInt &operator+=(const ModInt &o) {
        n += o.n;
        if (n >= MOD) {
            n -= MOD;}

        return *this;
    }
    
    ModInt &operator-=(const ModInt &o) {
        n -= o.n;
        if (n < 0) {
            n += MOD;}

        return *this;
    }
    
    ModInt &operator*=(const ModInt &o) {
        n = lng(n) * o.n % MOD;

        return *this;
    }

    ModInt &operator/=(const ModInt &o) {
        n = lng(n) * inv(o).n % MOD;

        return *this;
    }

    ModInt operator+() const {
        return *this;
    }
    
    ModInt operator-() const {
        return ModInt() - *this;
    }

    friend ModInt operator+(const ModInt &a, const ModInt &b) {
        return ModInt(a) += b;
    }
    
    friend ModInt operator-(const ModInt &a, const ModInt &b) {
        return ModInt(a) -= b;
    }

    friend ModInt operator*(const ModInt &a, const ModInt &b) {
        return ModInt(a) *= b;
    }
    
    friend ModInt operator/(const ModInt &a, const ModInt &b) {
        return ModInt(a) /= b;
    }

    // T: O(log(n))
    friend ModInt inv(ModInt a) {
        assert(a != 0);

        lng n = a.n, b = MOD, x = 1, y = 0;
        while (b > 0) {
            lng q = n / b;
            n = exchange(b, n - q * b);
            x = exchange(y, x - q * y);
        }

        return ModInt(x);
    }

    // T: O(log(n))
    friend ModInt pow(ModInt a, lng b) {
        if (b < 0) {
            return pow(inv(a), -b);}
        
        ModInt res = 1;
        while (b > 0) {
            if (b & 1) {
                res *= a;}
            
            a *= a;
            b >>= 1;
        }

        return res;
    }

    bool operator==(const ModInt &o) const {
        return n == o.n;
    }

    bool operator!=(const ModInt &o) const {
        return n != o.n;
    }

    bool operator<(const ModInt &o) const {
        return n < o.n;
    }

    bool operator>(const ModInt &o) const { 
        return o.n < n;
    }

    bool operator<=(const ModInt &o) const { 
        return !(o < *this); 
    }

    bool operator>=(const ModInt &o) const { 
        return !(*this < o); 
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        lng b;
        is >> b;
        a = ModInt(b);

        return is;
    }

    friend ostream &operator<<(ostream &os, const ModInt &a) {
        return os << a.n;
    }
};
using mint = ModInt<998'244'353>;

struct STTAlg {
    struct S { 
        mint sum;
        int len;
    };

    struct F {
        mint a, b;
        
        bool operator==(const F &o) const {
            return a == o.a && b == o.b;
        }

        bool operator!=(const F &o) const {
            return !(*this == o);
        }
    };

    static S idS() {
        return {0, 0};
    }

    static F idF() {
        return {1, 0};
    }

    static S defR(int l, int r) {
        return {0, r - l + 1};
    }

    static S init(int i, mint x) {
        return {x, 1};
    }

    static S ope(const S &a, const S &b) {
        if (a.len == 0) {
            return b;}

        if (b.len == 0) {
            return a;}
        
        S res;
        res.sum = a.sum + b.sum;
        res.len = a.len + b.len;

        return res;
    }

    static S map(const F &f, const S &a) {
        if (a.len == 0) {
            return a;}
        
        S res = a;
        res.sum = f.a * a.sum + f.b * a.len;
        
        return res;
    }

    static F cmp(const F &f, const F &g) {
        return {f.a * g.a, f.a * g.b + f.b};
    }
};

// S: O(n), U: O(log(n)), Q: O(log(n)), M: O(n)
template<typename STT>
struct SegTree {
    using S = typename STT::S;
    using F = typename STT::F;

    int n;
    vector<S> tree;
    vector<F> lazy;

    template<typename T>
    SegTree(const vector<T> &a): n(a.size()), tree(4 * a.size(), STT::idS()), lazy(4 * a.size(), STT::idF()) {
        build(1, 0, n - 1, a);
    }

    template<typename T>
    void build(int i, int l, int r, const vector<T> &a) {
        if (l == r) {
            tree[i] = STT::init(l, a[l]);
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * i,     l,     m, a);
        build(2 * i + 1, m + 1, r, a);
        tree[i] = STT::ope(tree[2 * i], tree[2 * i + 1]);
    }

    inline void apply(int i, F f) {
        tree[i] = STT::map(f, tree[i]);
        lazy[i] = STT::cmp(f, lazy[i]);
    }

    inline void push(int i) {
        if (lazy[i] == STT::idF()) {
            return;}
        
        apply(2 * i,     lazy[i]);
        apply(2 * i + 1, lazy[i]);
        lazy[i] = STT::idF();
    }

    void _update(int i, int l, int r, int ql, int qr, F f) {
        if (ql <= l && r <= qr) {
            apply(i, f);
            return;
        }

        push(i);
        
        int m = l + (r - l) / 2;
        if (ql <= m) {
            _update(2 * i,     l,     m, ql, qr, f);}
        if (qr > m)  {
            _update(2 * i + 1, m + 1, r, ql, qr, f);}
        tree[i] = STT::ope(tree[2 * i], tree[2 * i + 1]);
    }

    void update(int l, int r, F f) { 
        if (l >= 0 && l <= r && r < n) {
            _update(1, 0, n - 1, l, r, f);}
    }

    template<class G>
    int _maxR(int i, int l, int r, int ql, G &g, S &acc) {
        if (r < ql) {
            return -1;}
        
        if (ql <= l) {
            S nac = STT::ope(acc, tree[i]);
            if (g(nac)) {
                acc = nac;
                return -1;
            }
        }

        if (l == r) {
            return l - 1;} 

        push(i);
        int m = l + (r - l) / 2;
        int res = _maxR(2 * i, l, m, ql, g, acc);
        if (res != -1) {
            return res;}
        
        return _maxR(2 * i + 1, m + 1, r, ql, g, acc);
    }

    template<class G>
    int maxR(int l, G g) { // Returns max r in [l, n - 1] where g(query(l, r)) is true. If g(a[l]) is false, returns l - 1.
        if (l < 0 || l > n - 1) {
            return l - 1;}

        S acc = STT::idS();
        int res = _maxR(1, 0, n - 1, l, g, acc);
        
        return res == -1 ? n - 1 : res;
    }

    template<class G>
    int _minL(int i, int l, int r, int qr, G &g, S &acc) {
        if (l > qr) {
            return -1;}
        
        if (r <= qr) {
            S nac = STT::ope(tree[i], acc);
            if (g(nac)) {
                acc = nac;
                return -1;
            }
        }

        if (l == r) {
            return l + 1;}

        push(i);
        int m = l + (r - l) / 2;
        int res = _minL(2 * i + 1, m + 1, r, qr, g, acc);
        if (res != -1) {
            return res;}

        return _minL(2 * i, l, m, qr, g, acc);
    }
    
    template<class G>
    int minL(int r, G g) { // Returns min l in [0, r] where g(query(l, r)) is true. If g(a[r]) is false, returns r + 1.
        if (r < 0 || r > n - 1) {
            return r + 1;}

        S acc = STT::idS();
        int res = _minL(1, 0, n - 1, r, g, acc);
        
        return res == -1 ? 0 : res;
    }

    S _query(int i, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[i];}
        
        push(i);
        
        int m = l + (r - l) / 2;
        if (qr <= m) {
            return _query(2 * i,     l,     m, ql, qr);}
        if (ql > m)  {
            return _query(2 * i + 1, m + 1, r, ql, qr);}
        
        return STT::ope(_query(2 * i, l, m, ql, qr), _query(2 * i + 1, m + 1, r, ql, qr));
    }

    S query(int l, int r) { 
        if (l < 0 || r > n - 1 || l > r) {
            return STT::idS();}
        
        return _query(1, 0, n - 1, l, r); 
    }

    // Q: O(1)
    S queryAll() {
        return tree[1];
    }
};

// S: O(q * log(n)), U: O(log(n)), Q: O(log(n)), M: O(q * log(n))
template<typename STT>
struct DynSegTree {
    using S = typename STT::S;
    using F = typename STT::F;

    struct Node {
        S val;
        F lzy;
        int lc = -1, rc = -1;

        Node(lng l, lng r): val(STT::defR(l, r)), lzy(STT::idF()) {}
    };

    lng n;
    int root = -1;
    vector<Node> tree;
    
    DynSegTree(lng N): n(N) {
        tree.reserve(500'000);
        root = createNode(0, n - 1);
    }

    template<typename T>
    DynSegTree(const vector<T> &a): n(a.size()) {
        tree.reserve(4 * n);
        root = build(0, n - 1, a);
    }

    // S: O(n)
    template<typename T>
    int build(lng l, lng r, const vector<T> &a) {
        int cur = createNode(l, r);
        
        if (l == r) {
            tree[cur].val = STT::init(l, a[l]);
            return cur;
        }

        lng m = l + (r - l) / 2;
        int nlc = build(l,     m, a);
        tree[cur].lc = nlc;
        int nrc = build(m + 1, r, a);
        tree[cur].rc = nrc;
        tree[cur].val = STT::ope(tree[nlc].val, tree[nrc].val);

        return cur;
    }

    int createNode(lng l, lng r) {
        tree.emplace_back(l, r);
        
        return tree.size() - 1;
    }

    inline void apply(int i, F f) {
        tree[i].val = STT::map(f, tree[i].val);
        tree[i].lzy = STT::cmp(f, tree[i].lzy);
    }

    inline void push(int i, lng l, lng r) {
        if (tree[i].lzy == STT::idF()) {
            return;}
        
        lng m = l + (r - l) / 2;
        if (tree[i].lc == -1) {
            int nlc = createNode(l, m);
            tree[i].lc = nlc;
        }
        if (tree[i].rc == -1) {
            int nrc = createNode(m + 1, r);
            tree[i].rc = nrc;
        }

        apply(tree[i].lc, tree[i].lzy);
        apply(tree[i].rc, tree[i].lzy);
        tree[i].lzy = STT::idF();
    }

    void _update(int i, lng l, lng r, lng ql, lng qr, F f) {
        if (ql <= l && r <= qr) {
            apply(i, f);
            return;
        }

        push(i, l, r);
        
        lng m = l + (r - l) / 2;
        if (ql <= m) {
            if (tree[i].lc == -1) {
                int nlc = createNode(l, m);
                tree[i].lc = nlc;
            }

            _update(tree[i].lc, l,     m, ql, qr, f);
        }
        if (qr > m) {
            if (tree[i].rc == -1) {
                int nrc = createNode(m + 1, r);
                tree[i].rc = nrc;
            }

            _update(tree[i].rc, m + 1, r, ql, qr, f);
        }

        S l_val = tree[i].lc != -1 ? tree[tree[i].lc].val : STT::defR(l, m);
        S r_val = tree[i].rc != -1 ? tree[tree[i].rc].val : STT::defR(m + 1, r);
        tree[i].val = STT::ope(l_val, r_val);
    }

    void update(lng l, lng r, F f) { 
        if (l >= 0 && l <= r && r < n) {
            _update(root, 0, n - 1, l, r, f);}
    }

    template<class G>
    lng _maxR(int i, lng l, lng r, lng ql, G &g, S &acc) {
        if (r < ql) {
            return -1;}
        
        if (ql <= l) {
            S nac = STT::ope(acc, i == -1 ? STT::defR(l, r) : tree[i].val);
            if (g(nac)) {
                acc = nac;
                return -1;
            }
        }

        if (l == r) {
            return l - 1;}

        if (i != -1) {
            push(i, l, r);}

        lng m = l + (r - l) / 2;
        lng res = _maxR(i == -1 ? -1 : tree[i].lc, l, m, ql, g, acc);
        if (res != -1) {
            return res;}
        
        return _maxR(i == -1 ? -1 : tree[i].rc, m + 1, r, ql, g, acc);
    }

    template<class G>
    lng maxR(lng l, G g) { // Returns max r in [l, n - 1] where g(query(l, r)) is true. If g(a[l]) is false, returns l - 1.
        if (l < 0 || l > n - 1) {
            return l - 1;}

        S acc = STT::idS();
        lng res = _maxR(root, 0, n - 1, l, g, acc);

        return res == -1 ? n - 1 : res;
    }

    template<class G>
    lng _minL(int i, lng l, lng r, lng qr, G &g, S &acc) {
        if (l > qr) {
            return -1;}
        
        if (r <= qr) {
            S nac = STT::ope(i == -1 ? STT::defR(l, r) : tree[i].val, acc);
            if (g(nac)) {
                acc = nac;
                return -1;
            }
        }

        if (l == r) {
            return l + 1;}

        if (i != -1) {
            push(i, l, r);}

        lng m = l + (r - l) / 2;
        lng res = _minL(i == -1 ? -1 : tree[i].rc, m + 1, r, qr, g, acc);
        if (res != -1) {
            return res;}
        
        return _minL(i == -1 ? -1 : tree[i].lc, l, m, qr, g, acc);
    }

    template<class G>
    lng minL(lng r, G g) { // Returns min l in [0, r] where g(query(l, r)) is true. If g(a[r]) is false, returns r + 1.
        if (r < 0 || r > n - 1) {
            return r + 1;}
        
        S acc = STT::idS();
        lng res = _minL(root, 0, n - 1, r, g, acc);
        
        return res == -1 ? 0 : res;
    }

    S _query(int i, lng l, lng r, lng ql, lng qr) {
        if (i == -1) {
            if (max(l, ql) > min(r, qr)) {
                return STT::idS();}

            return STT::defR(max(l, ql), min(r, qr));
        }

        if (ql <= l && r <= qr) {
            return tree[i].val;}
        
        push(i, l, r);
        
        lng m = l + (r - l) / 2;
        if (qr <= m) {
            return _query(tree[i].lc, l    , m, ql, qr);}
        if (ql > m) {
            return _query(tree[i].rc, m + 1, r, ql, qr);}
        
        return STT::ope(_query(tree[i].lc, l, m, ql, qr), _query(tree[i].rc, m + 1, r, ql, qr));
    }

    S query(lng l, lng r) { 
        if (l < 0 || r > n - 1 || l > r) {
            return STT::idS();}

        return _query(root, 0, n - 1, l, r); 
    }

    // Q: O(1)
    S queryAll() {
        return root == -1 ? STT::defR(0, n - 1) : tree[root].val;
    }
};

// S: O(q * log(n)), U: O(log(n)), Q: O(log(n)), M: O(q * log(n))
template<typename STT>
struct PerSegTree {
    using S = typename STT::S;
    using F = typename STT::F;

    struct Node {
        S val;
        F lzy;
        int lc = -1, rc = -1;

        Node(lng l, lng r): val(STT::defR(l, r)), lzy(STT::idF()) {}
    };

    lng n;
    vector<int> roots;
    vector<Node> tree;

    PerSegTree(lng N): n(N) {
        tree.reserve(10'000'000); 
        roots.pb(cloneNode(-1, 0, n - 1));
    }

    template<typename T>
    PerSegTree(const vector<T> &a): n(a.size()) {
        tree.reserve(10'000'000); 
        roots.pb(build(0, n - 1, a));
    }

    // S: O(n)
    template<typename T>
    int build(lng l, lng r, const vector<T> &a) {
        int cur = cloneNode(-1, l, r);
        
        if (l == r) {
            tree[cur].val = STT::init(l, a[l]);
            return cur;
        }

        lng m = l + (r - l) / 2;
        int nlc = build(l,     m, a);
        tree[cur].lc = nlc;
        int nrc = build(m + 1, r, a);
        tree[cur].rc = nrc;
        tree[cur].val = STT::ope(tree[nlc].val, tree[nrc].val);

        return cur;
    }

    int cloneNode(int i, lng l, lng r) {
        if (i == -1) {
            tree.emplace_back(l, r);
        } else {
            Node tmp = tree[i];
            tree.pb(tmp);
        }

        return tree.size() - 1;
    }

    inline void apply(int i, F f) {
        tree[i].val = STT::map(f, tree[i].val);
        tree[i].lzy = STT::cmp(f, tree[i].lzy);
    }

    inline void push(int i, lng l, lng r) {
        if (tree[i].lzy == STT::idF()) {
            return;}
        
        lng m = l + (r - l) / 2;
        int nlc = cloneNode(tree[i].lc, l,     m);
        tree[i].lc = nlc;
        int nrc = cloneNode(tree[i].rc, m + 1, r);
        tree[i].rc = nrc;

        apply(tree[i].lc, tree[i].lzy);
        apply(tree[i].rc, tree[i].lzy);
        tree[i].lzy = STT::idF();
    }

    int _modify(int i1, int i2, lng l, lng r, lng ql, lng qr, F acc) {
        if (ql <= l && r <= qr) {
            int j = cloneNode(i2, l, r);
            apply(j, acc);
            return j;
        }

        int j = cloneNode(i1, l, r);
       
        push(j, l, r);

        int lc2 = -1, rc2 = -1;
        F nac = acc;
        if (i2 != -1) {
            lc2 = tree[i2].lc;
            rc2 = tree[i2].rc;
            nac = STT::cmp(acc, tree[i2].lzy);
        }

        lng m = l + (r - l) / 2;
        if (ql <= m) {
            int nlc = _modify(tree[j].lc, lc2, l,     m, ql, qr, nac);
            tree[j].lc = nlc;
        }
        if (qr > m) {
            int nrc = _modify(tree[j].rc, rc2, m + 1, r, ql, qr, nac);
            tree[j].rc = nrc;
        }

        S l_val = tree[j].lc != -1 ? tree[tree[j].lc].val : STT::defR(l, m);
        S r_val = tree[j].rc != -1 ? tree[tree[j].rc].val : STT::defR(m + 1, r);
        tree[j].val = STT::ope(l_val, r_val);

        return j;
    }

    int modify(int ver1, int ver2, lng l, lng r) {
        if (l < 0 || r > n - 1 || l > r) {
            int cur = roots[ver1];
            roots.pb(cur);
            return roots.size() - 1;
        }
        
        int cur = _modify(roots[ver1], roots[ver2], 0, n - 1, l, r, STT::idF());
        roots.pb(cur);
        
        return roots.size() - 1;
    }

    int _update(int i, lng l, lng r, lng ql, lng qr, F f) {
        int j = cloneNode(i, l, r);
        
        if (ql <= l && r <= qr) {
            apply(j, f);
            return j;
        }

        push(j, l, r);
        
        lng m = l + (r - l) / 2;
        if (ql <= m) {
            int nlc = _update(tree[j].lc, l,     m, ql, qr, f);
            tree[j].lc = nlc;
        }
        if (qr > m)  {
            int nrc = _update(tree[j].rc, m + 1, r, ql, qr, f);
            tree[j].rc = nrc;
        }

        S l_val = tree[j].lc != -1 ? tree[tree[j].lc].val : STT::defR(l, m);
        S r_val = tree[j].rc != -1 ? tree[tree[j].rc].val : STT::defR(m + 1, r);
        tree[j].val = STT::ope(l_val, r_val);
        
        return j;
    }

    int update(int ver, lng l, lng r, F f) { 
        if (l < 0 || r > n - 1 || l > r) {
            int cur = roots[ver];
            roots.pb(cur);
            return roots.size() - 1;
        }
        
        int cur = _update(roots[ver], 0, n - 1, l, r, f);
        roots.pb(cur);

        return roots.size() - 1;
    }

    template<class G>
    lng _maxR(int i, lng l, lng r, lng ql, G &g, S &acc, F tac) {
        if (r < ql) {
            return -1;}
        
        if (ql <= l) {
            S val = i == -1 ? STT::defR(l, r) : tree[i].val;
            val = STT::map(tac, val);
            S nac = STT::ope(acc, val);
            if (g(nac)) {
                acc = nac;
                return -1;
            }
        }

        if (l == r) {
            return l - 1;}

        tac = i == -1 ? tac : STT::cmp(tac, tree[i].lzy);
 
        lng m = l + (r - l) / 2;
        lng res = _maxR(i == -1 ? -1 : tree[i].lc, l, m, ql, g, acc, tac);
        if (res != -1) {
            return res;}
        
        return _maxR(i == -1 ? -1 : tree[i].rc, m + 1, r, ql, g, acc, tac);
    }

    template<class G>
    lng maxR(int ver, lng l, G g) { // Returns max r in [l, n - 1] where g(query(l, r)) is true. If g(a[l]) is false, returns l - 1.
        if (l < 0 || l > n - 1) {
            return l - 1;}

        S acc = STT::idS();
        lng res = _maxR(roots[ver], 0, n - 1, l, g, acc, STT::idF());
        
        return res == -1 ? n - 1 : res;
    }

    template<class G>
    lng _minL(int i, lng l, lng r, lng qr, G &g, S &acc, F tac) {
        if (l > qr) {
            return -1;}
        
        if (r <= qr) {
            S val = i == -1 ? STT::defR(l, r) : tree[i].val;
            val = STT::map(tac, val);
            S nac = STT::ope(val, acc);
            if (g(nac)) {
                acc = nac;
                return -1;
            }
        }

        if (l == r) {
            return l + 1;}
        
        tac = i == -1 ? tac : STT::cmp(tac, tree[i].lzy);

        lng m = l + (r - l) / 2;
        lng res = _minL(i == -1 ? -1 : tree[i].rc, m + 1, r, qr, g, acc, tac);
        if (res != -1) {
            return res;}
        
        return _minL(i == -1 ? -1 : tree[i].lc, l, m, qr, g, acc, tac);
    }

    template<class G>
    lng minL(int ver, lng r, G g) { // Returns min l in [0, r] where g(query(l, r)) is true. If g(a[r]) is false, returns r + 1.
        if (r < 0 || r > n - 1) {
            return r + 1;}
        
        S acc = STT::idS();
        lng res = _minL(roots[ver], 0, n - 1, r, g, acc, STT::idF());
        
        return res == -1 ? 0 : res;
    }

    S _query(int i, lng l, lng r, lng ql, lng qr, F acc) {
        if (i == -1) {
            if (max(l, ql) > min(r, qr)) {
                return STT::idS();}

            return STT::map(acc, STT::defR(max(l, ql), min(r, qr))); 
        }

        if (ql <= l && r <= qr) {
            return STT::map(acc, tree[i].val);}

        F nac = STT::cmp(acc, tree[i].lzy); 

        lng m = l + (r - l) / 2;
        if (qr <= m) {
            return _query(tree[i].lc, l,     m, ql, qr, nac);}
        if (ql > m) {
            return _query(tree[i].rc, m + 1, r, ql, qr, nac);}
        
        return STT::ope(_query(tree[i].lc, l, m, ql, qr, nac), _query(tree[i].rc, m + 1, r, ql, qr, nac));
    }

    S query(int ver, lng l, lng r) { 
        if (l < 0 || r > n - 1 || l > r) {
            return STT::idS();}

        return _query(roots[ver], 0, n - 1, l, r, STT::idF()); 
    }

    // Q: O(1)
    S queryAll(int ver) {
        return roots[ver] == -1 ? STT::defR(0, n - 1) : tree[roots[ver]].val;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<mint> A(n);
    for (auto &a : A)
        cin >> a;

    PerSegTree<STTAlg> segt(A);
    
    while (q--) {
        int t;
        cin >> t;

        if (t == 0) {
            int k, l, r;
            mint b, c;
            cin >> k >> l >> r >> b >> c;

            segt.update(k + 1, l, r - 1, {b, c});
        } else if (t == 1) {
            int k, s, l, r;
            cin >> k >> s >> l >> r;

            segt.modify(k + 1, s + 1, l, r - 1);
        } else {
            int k, l, r;
            cin >> k >> l >> r;

            cout << segt.query(k + 1, l, r - 1).sum << endl;

            int cur = segt.roots.back();
            segt.roots.pb(cur);
        }
    }

    return 0;
}