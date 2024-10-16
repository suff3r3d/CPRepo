// from online git I don't remember, all credits go to them
template<
    typename T  // need to support +, -
> struct Fenwick2D {
    // 1-indexed
    int n1, n2;
    vector<vector<T>> f;

    Fenwick2D(int _n1, int _n2) : n1(_n1 + 1), n2(_n2 + 1), f(1+n1, vector<T> (1+n2, T(0))) {}
    Fenwick2D() {}
    // a[x][y] += val
    void update(ll x, ll y, T val) {
        assert(0 <= x && x < n1);
        assert(0 <= y && y < n2);
        ++x; ++y;
        for (int u = x; u <= n1; u += u & -u) {
            for (int v = y; v <= n2; v += v & -v) {
                f[u][v] += val;
            }
        }
    }

    T get(ll x1, ll y1, ll x2, ll y2) const { // [x1,y1] -> [x2,y2]
        return _get(x1, y1, x2 + 1, y2 + 1);
    }
    T get(ll x, ll y) const { // [0,0] -> [x,y]
        return _get(x + 1, y + 1);
    }

private:
    // return rect sum of [0, 0] -> [x-1, y-1]
    T _get(ll x, ll y) const {
        assert(0 <= x && x <= n1);
        assert(0 <= y && y <= n2);
        T res(0);
        for (int u = x; u > 0; u -= u & -u) {
            for (int v = y; v > 0; v -= v & -v) {
                res += f[u][v];
            }
        }
        return res;
    }

    // returns rect sum of [x1, y1] -> [x2-1, y2-1]
    T _get(ll x1, ll y1, ll x2, ll y2) {
        if (x1 == x2 || y1 == y2) return T(0);
        return get(x2, y2) - get(x1, y2) - get(x2, y1) + get(x1, y1);
    }
};