//Template from VNOI: https://wiki.vnoi.info/algo/trick/matrix-multiplication with some modification
// ofc this is 0-indexed
template<typename T>
struct matrix_mod {
    T add(T a, T b) {
        return ((a+MOD)%MOD + (b+MOD)%MOD)%MOD;
    }
    T mul(T a, T b) {
        a *= b;
        if (a > MOD) a %= MOD;
        return a;
    }
    vector <vector <T> > data;
 
    int row() const { return data.size(); }
    int col() const { return data[0].size(); }
 
    auto & operator [] (int i) { return data[i]; }
    const auto & operator[] (int i) const { return data[i]; }
 
    matrix_mod() = default;
    matrix_mod(int r, int c): data(r, vector <T> (c)) { }
    matrix_mod(const vector <vector <T> > &d): data(d) {
        assert(d.size());
        int size = d[0].size();
        assert(size);
        for (auto x : d) assert(x.size() == size);
    }
 
    friend ostream & operator << (ostream &out, const matrix_mod &d) {
        for (auto x : d.data) {
            for (auto y : x) out << y << ' ';
            out << '\n';
        }
        return out;
    }
 
    static matrix_mod identity(long long n) {
        matrix_mod a = matrix_mod(n, n);
        while (n--) a[n][n] = 1;
        return a;
    }
 
    matrix_mod operator * (const matrix_mod &b) {
        matrix_mod a = *this;
        assert(a.col() == b.row());
        matrix_mod c(a.row(), b.col());
        for (int i = 0; i < a.row(); ++i)
            for (int j = 0; j < b.col(); ++j)
                for (int k = 0; k < a.col(); ++k)
                    c[i][j] = add(c[i][j], mul(a[i][k], b[k][j]));
        return c;
    }
 
    matrix_mod pow(long long exp) {
        assert(row() == col());
        matrix_mod base = *this, ans = identity(row());
        for (; exp > 0; exp >>= 1, base = base * base)
            if (exp & 1) ans = ans * base;
        return ans;
    }
};