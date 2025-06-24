// #define endl "\n"
// rolling hash with one-based indexing
//
// usage Hash(s, BASE)
//
// query
//   hash.fwd(l, r) //get forward hash
//   hash.bwd(l, r) //get backward hash

// Test fwd: https://judge.yosupo.jp/submission/295331
// Test bwd: https://judge.yosupo.jp/submission/295333
struct DoubleHash {
  ll MOD0, MOD1;
  // vector<ll> hashL0, hashL1, hashR0, hashR1, pow0, pow1;
  vector<ll> hashL0, hashR0, pow0;
  vector<ll> hashL1, hashR1, pow1;
  DoubleHash(string &s, ll BASE, ll MOD0 = 1e9 + 7, ll MOD1 = 998244353): MOD0(MOD0), MOD1(MOD1) {
    int n = s.size() - 1;
    hashL0.assign(n + 2, 0); hashR0 = hashL0;
    hashL1.assign(n + 2, 0); hashR1 = hashL1;

    pow0.assign(n + 1, 0); pow0[0] = 1;
    pow1.assign(n + 1, 0); pow1[0] = 1;
    for(int i = 1; i <= n; i++) {
      pow0[i] = (pow0[i - 1] * BASE) % MOD0;
      pow1[i] = (pow1[i - 1] * BASE) % MOD1;
    }
    for(int i = 1; i <= n; i++) {
      hashL0[i] = (hashL0[i - 1] * BASE + s[i] - 'a' + 1) % MOD0;
      hashL1[i] = (hashL1[i - 1] * BASE + s[i] - 'a' + 1) % MOD1;
    }
    for(int i = n; i >= 1; i--) {
      hashR0[i] = (hashR0[i + 1] * BASE + s[i] - 'a' + 1) % MOD0;
      hashR1[i] = (hashR1[i + 1] * BASE + s[i] - 'a' + 1) % MOD1;
    }
  }
  pair<ll,ll> fwd(int i, int j) {
    ll c0 = 0, c1 = 0;
    c0 = (hashL0[j] - hashL0[i - 1] * pow0[j - i + 1] + MOD0 * MOD0) % MOD0;
    c1 = (hashL1[j] - hashL1[i - 1] * pow1[j - i + 1] + MOD1 * MOD1) % MOD1;
    return {c0,c1};
  }
  pair<ll,ll> bwd(int i, int j) {
    ll c0 = 0, c1 = 0;
    c0 = (hashR0[i] - hashR0[j + 1] * pow0[j - i + 1] + MOD0 * MOD0) % MOD0;
    c1 = (hashR1[i] - hashR1[j + 1] * pow1[j - i + 1] + MOD1 * MOD1) % MOD1;
    return {c0,c1};
  }
};
