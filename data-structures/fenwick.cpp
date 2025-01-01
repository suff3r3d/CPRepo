template <class T>
class fenwick {
  vector<T> a;
  int n;

public:
  // fenwick() {}
  // shouldn't allow this

  fenwick(int n_) : n(n_) {
    // check initial value
    a.assign(n + 5, static_cast<T>(0));
  }

  T query(int r) {
    T q = 0; // check default value of query
    for (; r > 0; r -= (r & -r)) {
      q += a[r]; // check query modification
    }
    return q;
  }

  T query(int l, int r) {
    return query(r) - query(l - 1);
  }

  void update(int r, T del) {
    for (; r <= n; r += (r & -r)) {
      a[r] += del; //check update rule
    }
  }

  // difference array
  T query_diff(int v) {
    return query(v);
  }

  void update_diff(int l, int r, T val) {
    update(l, val);
    if (r < n) update(r + 1, -val); // check rule
  }
};