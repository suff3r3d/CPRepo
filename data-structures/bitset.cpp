typedef unsigned long long u64;
struct Bitsex {
  using T = Bitsex;
  int n;
  vector<u64> dat;

  Bitsex(int _n = 0, int x = 0) : n(_n) {
    assert(x == 0 || x == 1);
    u64 v = (x == 0 ? 0 : -1);
    dat.assign((n + 63) >> 6, v); // ceil(n / 64)
    if (n) {
      dat.back() >>= (64 * dat.size()) - n;
    }
  }

  int size() { return n; }

  void resize(int size) {
    dat.resize((size + 63) >> 6);
    int rem = size & 63;
    if (rem != 0) {
      u64 mask = (u64(1) << rem) - 1;
      dat.back() &= mask;
    }
    n = size;
  }

  class Proxy {
  private:
    vector<u64> &dat;
    int index;

  public:
    Proxy(vector<u64> &d, int i) : dat(d), index(i) {}
    operator bool() const { return (dat[index >> 6] >> (index & 63)) & 1; }

    Proxy &operator=(u64 value) {
      dat[index >> 6] &= ~(u64(1) << (index & 63));
      dat[index >> 6] |= (value & 1) << (index & 63);
      return *this;
    }
    void flip() { dat[index >> 6] ^= (u64(1) << (index & 63)); }
  };

  Proxy operator[](int i) { return Proxy(dat, i); }

  bool operator==(const T &p) {
    assert(n == p.n);
    for (int i = 0; i < int(dat.size()); i++) {
      if (dat[i] != p.dat[i]) {
        return false;
      }
    }
    return true;
  }

  T &operator|=(const T &p) {
    assert(n == p.n);
    for (int i = 0; i < int(dat.size()); i++) {
      dat[i] |= p.dat[i];
    }
    return *this;
  }
  T &operator&=(const T &p) {
    assert(n == p.n);
    for (int i = 0; i < int(dat.size()); i++) {
      dat[i] &= p.dat[i];
    }
    return *this;
  }
  T &operator^=(const T &p) {
    assert(n == p.n);
    for (int i = 0; i < int(dat.size()); i++) {
      dat[i] ^= p.dat[i];
    }
    return *this;
  }

  T operator^(const T &p) const { return T(*this) ^= p; }
  T operator|(const T &p) const { return T(*this) |= p; }
  T operator&(const T &p) const { return T(*this) &= p; }

  static string TO_STR[256];
  string to_string() const {
    if (TO_STR[0].empty()) {
      precompute();
    }
    string s = "";
    for (auto &x : dat) {
      for (int i = 0; i < 8; i++) {
        s += TO_STR[(x >> (8 * i) & 255)];
      }
    }
    s.resize(n);
    return s;
  }

  static void precompute() {
    for (int i = 0; i < 256; i++) {
      string x;
      for (int j = 0; j < 8; j++) {
        x += '0' + (i >> j & 1);
      }
      TO_STR[i] = x;
    }
  }
};
string Bitsex::TO_STR[256];
