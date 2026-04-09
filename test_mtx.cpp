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

template<lng MOD>
struct ModInt {
    lng n;

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

template<typename T>
struct Matrix {
    int n, m;
    vector<vector<T>> v;

    Matrix(int N = 0, int M = 0): n(N), m(M), v(N, vector<T>(M, T(0))) {
        assert((n == 0 && m == 0) || (n > 0 && m > 0));
    }

    Matrix(const vector<T> &a, int axis = 0) {
        assert(!a.empty());

        if (axis == 0) {
            n = 1;
            m = a.size();
            v = {a};
        } else if (axis == 1) {
            n = a.size();
            m = 1;
            v.resize(n);
            for (int i = 0; i < n; i++) {
                v[i] = {a[i]};}
        }
    }

    Matrix(const vector<vector<T>> &a) {
        if (!a.empty()) {
            assert(!a[0].empty());}

        n = a.size();
        m = a.empty() ? 0 : a[0].size();
        v = a;
    }

    vector<T> &operator[](int i) { 
        return v[i]; 
    }
    
    const vector<T> &operator[](int i) const { 
        return v[i]; 
    }
    
    int size() const { 
        return n; 
    }

    Matrix &operator+=(const Matrix &o) {
        assert(n == o.n && m == o.m);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[i][j] += o[i][j];}}

        return *this;
    }

    Matrix &operator-=(const Matrix &o) {
        assert(n == o.n && m == o.m);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[i][j] -= o[i][j];}}

        return *this;
    }

    Matrix &operator*=(T o) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[i][j] *= o;}}

        return *this;
    }

    Matrix &operator*=(const vector<T> &o) {
        return *this = *this * o;
    }

    Matrix &operator*=(const Matrix &o) {
        return *this = *this * o;
    }
    
    Matrix &operator/=(T o) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[i][j] /= o;}}
        
        return *this;
    }

    Matrix &operator/=(const Matrix &o) {
        return *this = *this / o;
    }

    Matrix &operator%=(T o) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                v[i][j] %= o;}}
        
        return *this;
    }

    Matrix operator+() const {
        return *this;
    }

    Matrix operator-() const {
        Matrix res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res[i][j] = -v[i][j];}}

        return res;
    }

    friend Matrix operator+(Matrix a, const Matrix &b) {
        return a += b;
    }

    friend Matrix operator-(Matrix a, const Matrix &b) {
        return a -= b;
    }

    friend Matrix operator*(Matrix a, T b) {
        return a *= b;
    }

    friend Matrix operator*(T b, Matrix a) {
        return a *= b;
    }

    friend Matrix operator*(const vector<T> &b, Matrix a) {
        return Matrix(b, 0) *= a;
    }

    friend Matrix operator*(Matrix a, const vector<T> &b) {
        return a *= Matrix(b, 1);
    }

    friend Matrix operator*(const Matrix &a, const Matrix &b) {
        assert(a.m == b.n);

        Matrix res(a.n, b.m);
        for (int i = 0; i < a.n; i++) {
            for (int k = 0; k < a.m; k++) {
                if (a[i][k] == T(0)) {
                    continue;}
                
                T a_ik = a[i][k]; 
                for (int j = 0; j < b.m; j++) {
                    res[i][j] += a_ik * b[k][j];}
            }
        }

        return res;
    }

    friend Matrix operator/(Matrix a, T b) {
        return a /= b;
    }

    friend Matrix operator/(const Matrix &a, const Matrix &b) {
        assert(a.m == b.n);

        return a * inv(b);
    }

    friend Matrix operator%(Matrix a, T b) {
        return a %= b;
    }

    friend Matrix add(const Matrix &a, const Matrix &b, int axis = 0) {
        Matrix res;
        if (axis == 0) {
            assert(a.n == b.n);

            res = Matrix(a.n, a.m + b.m);
            for (int i = 0; i < a.n; i++) {
                for (int j = 0; j < a.m; j++) {
                    res[i][j] = a[i][j];}}
            for (int i = 0; i < b.n; i++) {
                for (int j = 0; j < b.m; j++) {
                    res[i][j + a.m] = b[i][j];}}
        } else if (axis == 1) {
            assert(a.m == b.m);

            res = Matrix(a.n + b.n, a.m);
            for (int i = 0; i < a.n; i++) {
                for (int j = 0; j < a.m; j++) {
                    res[i][j] = a[i][j];}}
            for (int i = 0; i < b.n; i++) {
                for (int j = 0; j < b.m; j++) {
                    res[i + a.n][j] = b[i][j];}}
        }

        return res;
    }

    friend T det(Matrix a) {
        static_assert(!std::is_integral_v<T>);
        assert(a.n == a.m);

        T res = 1;
        for (int i = 0; i < a.n; i++) {
            int piv = i;
            while (piv < a.n && a[piv][i] == T(0)) {
                piv++;}
            if (piv == a.n) {
                return T(0);}
            
            if (i != piv) {
                swap(a[i], a[piv]);
                res = -res;
            }
            
            res *= a[i][i];
            T d = T(1) / a[i][i];
            for (int j = i; j < a.n; j++) {
                a[i][j] *= d;}
            
            for (int k = i + 1; k < a.n; k++) {
                if (a[k][i] == T(0)) {
                    continue;}
                
                T a_ki = a[k][i];
                for (int j = i; j < a.n; j++) {
                    a[k][j] -= a[i][j] * a_ki;}
            }
        }

        return res;
    }

    friend Matrix inv(Matrix a) {
        static_assert(!std::is_integral_v<T>);
        assert(a.n == a.m);

        Matrix res = eye(a.n, a.n);
        for (int i = 0; i < a.n; i++) {
            int piv = i;
            while (piv < a.n && a[piv][i] == T(0)) {
                piv++;}

            assert(piv < a.n);

            if (i != piv) {
                swap(a[i], a[piv]);
                swap(res[i], res[piv]);
            }

            T d = T(1) / a[i][i];
            for (int j = i; j < a.n; j++) {
                a[i][j] *= d;}
            for (int j = 0; j < a.n; j++) {
                res[i][j] *= d;}

            for (int k = 0; k < a.n; k++) {
                if (k == i) {
                    continue;}

                T a_ki = a[k][i];
                if (a_ki == T(0)) {
                    continue;}
                
                for (int j = i; j < a.n; j++) {
                    a[k][j] -= a[i][j] * a_ki;}
                for (int j = 0; j < a.n; j++) {
                    res[k][j] -= res[i][j] * a_ki;}
            }
        }

        return res;
    }

    friend Matrix pow(Matrix a, lng b) {
        assert(a.n == a.m && b >= 0);
        
        Matrix res = eye(a.n, a.n);
        while (b > 0) {
            if (b & 1) {
                res *= a;}

            b >>= 1;
            if (b == 0) {
                break;}

            a *= a;
        }

        return res;
    }

    friend Matrix ref(Matrix a) {
        static_assert(!std::is_integral_v<T>);
        
        int r = 0;
        for (int c = 0; r < a.n && c < a.m; c++) {
            int piv = r;
            while (piv < a.n && a[piv][c] == T(0)) {
                piv++;}
            
            if (piv == a.n) {
                continue;}
            
            if (r != piv) {
                swap(a[r], a[piv]);}
            
            T d = T(1) / a[r][c];
            for (int j = c; j < a.m; j++) {
                a[r][j] *= d;}
            
            for (int i = r + 1; i < a.n; i++) {
                T a_ic = a[i][c];
                if (a_ic == T(0)) {
                    continue;}
                
                for (int j = c; j < a.m; j++) {
                    a[i][j] -= a[r][j] * a_ic;}
            }
            r++;
        }

        return a;
    }

    friend Matrix rref(Matrix a) {
        static_assert(!std::is_integral_v<T>, "Division optimization not safe for integer types.");
        
        int r = 0;
        for (int c = 0; r < a.n && c < a.m; c++) {
            int piv = r;
            while (piv < a.n && a[piv][c] == T(0)) {
                piv++;}
            
            if (piv == a.n) {
                continue;}
            
            if (r != piv) {
                swap(a[r], a[piv]);}
            
            T d = T(1) / a[r][c];
            for (int j = c; j < a.m; j++) {
                a[r][j] *= d;}
            
            for (int i = 0; i < a.n; i++) {
                if (i == r) {
                    continue;}
                
                T a_ic = a[i][c];
                if (a_ic == T(0)) {
                    continue;}
                
                for (int j = c; j < a.m; j++) {
                    a[i][j] -= a[r][j] * a_ic;}
            }
            r++;
        }

        return a;
    }

    friend T trace(const Matrix &a) {
        assert(a.n == a.m);

        T res = 0;
        for (int i = 0; i < a.n; i++) {
            res += a[i][i];}

        return res;
    }

    friend Matrix trp(const Matrix &a) { 
        Matrix res(a.m, a.n);
        for (int i = 0; i < a.m; i++) {
            for (int j = 0; j < a.n; j++) {
                res[i][j] = a[j][i];}}
        
        return res;
    }

    static Matrix cross(const Matrix &a, const Matrix &b, int axis = 0) {
        assert((a.n == 1 || a.m == 1) && max(a.n, a.m) == 3);
        assert((b.n == 1 || b.m == 1) && max(b.n, b.m) == 3);

        auto get = [](const Matrix &x, int i) {
            return x.n == 1 ? x[0][i] : x[i][0];
        };

        T x = get(a, 1) * get(b, 2) - get(a, 2) * get(b, 1);
        T y = get(a, 2) * get(b, 0) - get(a, 0) * get(b, 2);
        T z = get(a, 0) * get(b, 1) - get(a, 1) * get(b, 0);

        return Matrix(vector<T>({x, y, z}), axis);
    }

    static T dot(const Matrix &a, const Matrix &b) {
        assert((a.n == 1 || a.m == 1) && (b.n == 1 || b.m == 1));
        assert(max(a.n, a.m) == max(b.n, b.m));

        auto get = [](const Matrix &x, int i) {
            return x.n == 1 ? x[0][i] : x[i][0];
        };

        T res = 0;
        for (int i = 0; i < max(a.n, a.m); i++) {
            res += get(a, i) * get(b, i);}

        return res;
    }

    static Matrix eye(int N, int M) {
        Matrix res(N, M);
        for (int i = 0; i < min(N, M); i++) {
            res[i][i] = T(1);}      
        
        return res;
    }

    friend bool operator==(const Matrix &a, const Matrix &b) {
        return a.v == b.v;
    }

    friend bool operator!=(const Matrix &a, const Matrix &b) {
        return a.v != b.v;
    }

    friend ostream &operator<<(ostream &os, const Matrix &a) {
        if (a.n == 0 || a.m == 0) {
            return os;}
        
        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < a.m; j++) {
                os << a[i][j] << ' ';}

            if (i < a.n - 1) {
                os << '\n';}
        }
        
        return os;
    }
};
using mtx = Matrix<mint>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string op;
    while (cin >> op) {
        if (op == "add" || op == "sub" || op == "mul") {
            int n1, m1, n2, m2; cin >> n1 >> m1 >> n2 >> m2;
            mtx A(n1, m1), B(n2, m2);
            for(int i=0; i<n1; i++) for(int j=0; j<m1; j++) cin >> A[i][j];
            for(int i=0; i<n2; i++) for(int j=0; j<m2; j++) cin >> B[i][j];
            
            if (op == "add") cout << (A + B) << endl;
            else if (op == "sub") cout << (A - B) << endl;
            else cout << (A * B) << endl;
        }
        else if (op == "pow") {
            int n; lng exp; cin >> n >> exp;
            mtx A(n, n);
            for(int i=0; i<n; i++) for(int j=0; j<n; j++) cin >> A[i][j];
            cout << pow(A, exp) << endl;
        }
        else if (op == "det" || op == "trace") {
            int n; cin >> n;
            mtx A(n, n);
            for(int i=0; i<n; i++) for(int j=0; j<n; j++) cin >> A[i][j];
            
            if (op == "det") cout << det(A) << endl;
            else cout << trace(A) << endl;
        }
        else if (op == "inv" || op == "ref" || op == "rref" || op == "trp") {
            int n, m; cin >> n >> m;
            mtx A(n, m);
            for(int i=0; i<n; i++) for(int j=0; j<m; j++) cin >> A[i][j];
            
            if (op == "inv") cout << inv(A) << endl;
            else if (op == "ref") cout << ref(A) << endl;
            else if (op == "rref") cout << rref(A) << endl;
            else cout << trp(A) << endl;
        }
        else if (op == "cross") {
            int n1, m1, n2, m2, axis; cin >> n1 >> m1 >> n2 >> m2 >> axis;
            mtx A(n1, m1), B(n2, m2);
            for(int i=0; i<n1; i++) for(int j=0; j<m1; j++) cin >> A[i][j];
            for(int i=0; i<n2; i++) for(int j=0; j<m2; j++) cin >> B[i][j];
            cout << mtx::cross(A, B, axis) << endl;
        }
        else if (op == "dot") {
            int n1, m1, n2, m2; cin >> n1 >> m1 >> n2 >> m2;
            mtx A(n1, m1), B(n2, m2);
            for(int i=0; i<n1; i++) for(int j=0; j<m1; j++) cin >> A[i][j];
            for(int i=0; i<n2; i++) for(int j=0; j<m2; j++) cin >> B[i][j];
            cout << mtx::dot(A, B) << endl;
        }
        else if (op == "concat") {
            int axis, n1, m1, n2, m2; cin >> axis >> n1 >> m1 >> n2 >> m2;
            mtx A(n1, m1), B(n2, m2);
            for(int i=0; i<n1; i++) for(int j=0; j<m1; j++) cin >> A[i][j];
            for(int i=0; i<n2; i++) for(int j=0; j<m2; j++) cin >> B[i][j];
            cout << add(A, B, axis) << endl;
        }
    }
    return 0;
}