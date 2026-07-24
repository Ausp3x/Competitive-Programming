// 知彼知己，百战不殆
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi    first
#define se    second
#define pb    push_back
using uint = uint32_t;
using lng = int64_t;    using ulng = uint64_t;
using lll = __int128_t; using ulll = __uint128_t;
template<typename T> 
using indexed_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int INF32 = 0x3f3f3f3f;
constexpr lng INF64 = 0x3f3f3f3f3f3f3f3f;

template<typename T> 
constexpr inline bool chmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template<typename T> 
constexpr inline bool chmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }

#ifdef LOCAL
namespace Debug {
    using std::to_string;

    inline string to_string(bool x) { return x ? "true" : "false"; }
    inline string to_string(char x) { return string({'\'', x, '\''}); }
    inline string to_string(lll x) {
        if (x == 0) { return "0"; }
        string s; bool is_neg = x < 0; 
        ulll ux = is_neg ? -ulll(x) : ulll(x);
        while (ux > 0) { s += char('0' + ux % 10); ux /= 10; }
        if (is_neg) { s += '-'; }
        std::reverse(s.begin(), s.end());
        return s;}
    inline string to_string(ulll x) {
        if (x == 0) { return "0"; }
        string s;
        while (x > 0) { s += char('0' + x % 10); x /= 10; }
        std::reverse(s.begin(), s.end());
        return s;}
    inline string to_string(std::string_view x) {
        string res; res.reserve(x.size() + 2);
        res += '"'; res += x; res += '"';
        return res;}
    inline string to_string(const char *x) { return x ? to_string(std::string_view(x)) : ""; }
    inline string to_string(char *x) { return to_string(static_cast<const char*>(x)); }
    inline string to_string(const string &x) { return to_string(std::string_view(x)); }
    template<size_t N> 
    inline string to_string(const bitset<N> &x) { return x.to_string(); }
    
    template<typename T>
    requires std::is_aggregate_v<T> && (!std::ranges::range<T>) 
          && (!requires (ostream &os, const T &x) { os << x; })
    inline string to_string(const T &x);
    
    template<typename T>
    requires requires { std::tuple_size<T>::value; } && (!std::ranges::range<T>)
    inline string to_string(const T &x);
    template<std::ranges::range T> 
    requires (!std::is_convertible_v<T, std::string_view>)
    inline string to_string(const T &x);
    template<typename T, typename C>
    inline string to_string(const queue<T, C> &x);
    template<typename T, typename C>
    inline string to_string(const stack<T, C> &x);
    template<typename T, typename C, typename Comp>
    inline string to_string(const priority_queue<T, C, Comp> &x);
    
    template<typename T>
    requires (!std::ranges::range<T>) && requires (ostream &os, const T &x) { os << x; }
    inline string to_string(const T &x) { std::stringstream ss; ss << x; return ss.str(); }
    
    // optional
    struct Any { template<typename T> operator T() const; };
    template<typename T, size_t N>
    constexpr bool aggSizGeq = []<size_t ...I>(std::index_sequence<I...>) {
        return requires { T{(void(I), Any{})...}; };}(std::make_index_sequence<N>{});
    template<typename T, size_t N>
    constexpr bool aggSizExact = aggSizGeq<T, N> && !aggSizGeq<T, N + 1>;
    template<typename T>
    requires std::is_aggregate_v<T> && (!std::ranges::range<T>) 
          && (!requires (ostream &os, const T &x) { os << x; })
    inline string to_string(const T &x) {
        if constexpr (aggSizExact<T, 8>) {
            auto &[a, b, c, d, e, f, g, h] = x; return to_string(std::tie(a, b, c, d, e, f, g, h));} 
        else if constexpr (aggSizExact<T, 7>) {
            auto &[a, b, c, d, e, f, g] = x; return to_string(std::tie(a, b, c, d, e, f, g));} 
        else if constexpr (aggSizExact<T, 6>) {
            auto &[a, b, c, d, e, f] = x; return to_string(std::tie(a, b, c, d, e, f));} 
        else if constexpr (aggSizExact<T, 5>) {
            auto &[a, b, c, d, e] = x; return to_string(std::tie(a, b, c, d, e));} 
        else if constexpr (aggSizExact<T, 4>) {
            auto &[a, b, c, d] = x; return to_string(std::tie(a, b, c, d));} 
        else if constexpr (aggSizExact<T, 3>) {
            auto &[a, b, c] = x; return to_string(std::tie(a, b, c));} 
        else if constexpr (aggSizExact<T, 2>) {
            auto &[a, b] = x; return to_string(std::tie(a, b));} 
        else if constexpr (aggSizExact<T, 1>) {
            auto &[a] = x; return to_string(std::tie(a));} 
        else { return "{}"; }}
    
    template<typename T>
    requires requires { std::tuple_size<T>::value; } && (!std::ranges::range<T>)
    inline string to_string(const T &x) {
        string res = "(";
        std::apply([&](const auto &...args) { 
            int i = 0; ((res += (i++ ? ", " : ""), res += to_string(args)), ...);}, x);
        return res + ")";}
    template<std::ranges::range T> 
    requires (!std::is_convertible_v<T, std::string_view>)
    inline string to_string(const T &x) {
        int i = 0; string res = "{";
        for (auto &&y : x) {
            if (i++ > 0) { res += ", "; } 
            res += to_string(y);}
        res += "}";
        return res;}
    template<typename T, typename C>
    inline string to_string(const queue<T, C> &x) {
        struct Accessor : queue<T, C> { 
            static const C &get(const queue<T, C> &q) { return q.*&Accessor::c; }};
        return to_string(Accessor::get(x));}
    template<typename T, typename C>
    inline string to_string(const stack<T, C> &x) {
        struct Accessor : stack<T, C> { 
            static const C &get(const stack<T, C> &q) { return q.*&Accessor::c; }};
        return to_string(Accessor::get(x));}
    template<typename T, typename C, typename Comp>
    inline string to_string(const priority_queue<T, C, Comp> &x) {
        struct Accessor : priority_queue<T, C, Comp> { 
            static const C &get(const priority_queue<T, C, Comp> &q) { return q.*&Accessor::c; }};
        return to_string(Accessor::get(x));}

    inline int dep = 0;
    inline std::string_view indent() {
        static constexpr auto spaces = []() { array<char, 128> v{}; v.fill(' '); return v; }();
        return std::string_view(spaces.data(), min<int>(2 * dep, spaces.size()));}
    template<std::ranges::range R, typename ...Args>
    auto slice(R &&ran, int l, int r, Args ...args) {
        auto v = std::forward<R>(ran) | std::views::drop(l) | std::views::take(r - l + 1);
        if constexpr (sizeof...(args) == 0) { return v; } 
        else { return v | std::views::transform([=](auto &&cur) { return slice(cur, args...); }); }}

    template<typename ...Args>
    void debugO(const Args &...args) { ((cerr << ' ' << to_string(args)), ...); cerr << '\n'; }
    struct Tracer {
        string v; 
        Tracer(string x) : v(std::move(x)) { cerr << indent() << ">> " << v << '\n'; dep++; }
        ~Tracer() { dep--; cerr << indent() << "<< " << v << '\n'; }};
}

#define debug(...) cerr << Debug::indent() << "[L" << __LINE__ << "] [" << #__VA_ARGS__ << "]", Debug::debugO(__VA_ARGS__)
// #define debug(...) cerr << Debug::indent() << "\033[1;31m[L" << __LINE__ << "] [" << #__VA_ARGS__ << "]:\033[0m", Debug::debugO(__VA_ARGS__)
#define TRACE_CNCAT(a, b) a##b
#define TRACE_GUARD(a, b) TRACE_CNCAT(a, b)
#define trace(x) Debug::Tracer TRACE_GUARD(_traceGuard, __LINE__)(x)
#else
#define debug(...) void(0)
#define trace(x) void(0)
#endif

// T: O(1) or O(log(n)), M: O(1)
template<int ID = 0>
struct DynModInt {
    static inline int MOD = 998'244'353;
    static inline ulng IMOD = -1ULL / 998'244'353 + 1;
    static inline bool is_prime = true;
    static bool isPrime() {
        if (MOD <= 1) { return false; }
        if (MOD == 2 || MOD == 7 || MOD == 61) { return true; }
        if (!(MOD & 1)) { return false; }
        int s = __builtin_ctzll(MOD - 1); lng d = lng(MOD - 1) >> s;
        for (lng a : {2, 7, 61}) {
            lng x = 1;
            for (lng b = d; b > 0; b >>= 1) {
                if (b & 1) { x = x * a % MOD; }
                a = a * a % MOD;}
            if (x == 1 || x == MOD - 1) { continue; }
            bool is_comp = true;
            for (int j = 1; j < s; j++) {
                x = x * x % MOD;
                if (x == MOD - 1) { is_comp = false; break; }
                if (x == 1) { return false; }}
            if (is_comp) { return false; }}
        return true;}
    static void setMod(int mod, int prm = -1) {
        assert(mod > 0 && -1 <= prm && prm <= 1);
        MOD = mod; IMOD = (mod != 1) * (-1ULL / mod + 1);
        is_prime = prm == -1 ? isPrime() : prm;}
    static uint red(ulng a) {
        if (MOD == 1) { return 0; }
        ulng q = ulng((ulll(a) * IMOD) >> 64);
        ulng r = a - q * MOD;
        if (MOD <= r) { r += MOD; }
        return uint(r);}
    template<typename T>
    requires std::is_integral_v<T> || std::is_same_v<T, lll> || std::is_same_v<T, ulll>
    static int norm(T a) {
        if constexpr (std::is_same_v<T, ulll>) { return a % MOD; } 
        else if constexpr (std::is_same_v<T, lll>) { a %= MOD; return a + (a < 0) * MOD; } 
        else if constexpr (std::is_signed_v<T>) {
            if (a >= 0) { return red(a); }
            uint res = red(-ulng(a)); 
            return (res != 0) * (MOD - res);}
        else { return red(a); }}

    int n;
    template<typename T = int> 
    requires std::is_integral_v<T> || std::is_same_v<T, lll> || std::is_same_v<T, ulll>
    DynModInt(T N = 0) : n(norm(N)) {}
    
    explicit operator int() const { return n; }
    static DynModInt init(int N) { DynModInt res; res.n = N; return res; }
    template<typename T> 
    requires std::is_integral_v<T> || std::is_same_v<T, lll> || std::is_same_v<T, ulll>
    DynModInt &operator=(T N) { n = norm(N); return *this; }
    
    DynModInt &operator++() { n++; n -= (n == MOD) * MOD; return *this; }
    DynModInt &operator--() { n += (n == 0) * MOD; n--; return *this; }
    DynModInt operator++(int) { DynModInt res = *this; ++*this; return res; }
    DynModInt operator--(int) { DynModInt res = *this; --*this; return res; }
    DynModInt &operator+=(DynModInt o) { n += o.n - (n >= MOD - o.n) * MOD; return *this; }
    DynModInt &operator-=(DynModInt o) { n -= o.n - (n < o.n) * MOD; return *this; }
    DynModInt &operator*=(DynModInt o) { n = red(1ULL * n * o.n); return *this; }
    DynModInt &operator/=(DynModInt o) { return *this *= inv(o); }

    DynModInt operator+() const { return *this; }
    DynModInt operator-() const { return init((n != 0) * (MOD - n)); }
    friend DynModInt operator+(DynModInt a, DynModInt b) { a += b; return a; }
    friend DynModInt operator-(DynModInt a, DynModInt b) { a -= b; return a; }
    friend DynModInt operator*(DynModInt a, DynModInt b) { a *= b; return a; }
    friend DynModInt operator/(DynModInt a, DynModInt b) { a /= b; return a; }
    
    // T: O(log(n))
    friend DynModInt inv(DynModInt a) {
        assert(a != 0);
        if (is_prime) { return pow(a, MOD - 2); }
        int n = a.n, b = MOD, x = 1, y = 0;
        while (b > 0) {
            int q = n / b;
            n = std::exchange(b, n - q * b);
            x = std::exchange(y, x - q * y);}
        assert(n == 1);
        return init(x + (x < 0) * MOD);}
    // T: O(log(n))
    friend DynModInt pow(DynModInt a, lng b) {
        ulng ub = b < 0 ? -ulng(b) : ulng(b);
        if (b < 0) { a = inv(a); }
        DynModInt res = 1;
        for (; ub > 0; ub >>= 1, a *= a) { if (ub & 1) { res *= a; } }
        return res;}
    // T: O(log(n)) average
    friend DynModInt sqrt(DynModInt a) {
        assert(is_prime);
        if (a == 0 || MOD == 2) { return a; }
        if (pow(a, (MOD - 1) / 2) != 1) { return -1; }
        DynModInt b = 1;
        while (pow(b * b - a, (MOD - 1) / 2) == 1) { b++; }
        struct Node {
            DynModInt x, y, w;
            Node(DynModInt X = 0, DynModInt Y = 0, DynModInt W = 0) : x(X), y(Y), w(W) {}
            Node operator*(const Node &o) const { 
                return Node(x * o.x + y * o.y * w, x * o.y + y * o.x, w); }};
        Node res(1, 0, b * b - a), cur(b, 1, b * b - a);
        for (lng p = (lng(MOD) + 1) / 2; p > 0; p >>= 1, cur = cur * cur) {
            if (p & 1) { res = res * cur; }}
        return init(min(res.x.n, MOD - res.x.n));}

    explicit operator bool() const { return n != 0; }
    bool operator!() const { return n == 0; }
    friend auto operator<=>(const DynModInt &a, const DynModInt &b) = default;
    
    friend istream &operator>>(istream &is, DynModInt &a) { lng b; if (is >> b) { a = b; } return is; }
    friend ostream &operator<<(ostream &os, DynModInt a) { return os << a.n; }
};
using mint = DynModInt<1>;

void solve(int t) {
    // trace(to_string(t));

    int n, m;
    cin >> n >> m;
    mint::setMod(m);
    vector<mint> A(n);
    for (mint &a : A) {
        cin >> a;
    }
    vector<mint> B(n - 1);
    for (mint &b : B) {
        cin >> b;
    }

    mint req = 0;
    lng cur = 0;
    vector<pair<lng, lng>> E;
    for (int i = 0; i < n; i++) {
        lng cost = int(req - A[i]);
        cur += cost;
        lng pos, ext;
        if (i % 2 == 0) {
            pos = (m - 1 - cost + m) % m;
            ext = -m;
        } else {
            pos = cost;
            ext = m;
        }
        
        if (i < n - 1) {
            req = B[i] - req;
        }
        if (pos < m - 1) {
            E.pb({pos, ext});
        }
    }

    sort(E.begin(), E.end());

    lng ans = cur, a = 0;
    for (int i = 0; i < E.size();) {
        lng pos = E[i].fi;
        cur += (pos - a) * (n % 2);
        chmin(ans, cur);

        lng ext = 0;
        while (E[i].fi == pos && i < E.size()) {
            ext += E[i].se;
            i++;
        }

        cur += (n % 2) + ext;
        chmin(ans, cur);
        a = pos + 1;
    }

    cur += (m - 1 - a) * (n % 2);
    chmin(ans, cur);

    cout << ans << endl;

    return;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++) {
        solve(i);
    }

    return 0;
}