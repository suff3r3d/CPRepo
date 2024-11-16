vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);
 
Mint power(const Mint a, const int b) {
  assert(b >= 0);
  Mint x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}

Mint C(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  k = min(k, n - k);
  while ((int) fact.size() < n + 1) {
    fact.push_back(fact.back() * (int) fact.size());
    inv_fact.push_back(1 / fact.back());
  }
  return fact[n] * inv_fact[k] * inv_fact[n - k];
}
