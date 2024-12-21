/**
 * This is chungdinh's version of LCA
 * Allows tree to have weight
 * 
 * + No 2_i-th parent is -1
 * 
 * + add graph reference (I use g, distiled use adj)
 * + custom merge
 */
 
struct LCA {
  // using ii = pair<long long, long long>;
  // using ll = long long;
 
  vector<vector<int>> par;
  vector<vector<ll>> val;
  vector<int> dep;
  int LG; 
 
  vector<vector<ii>>& adj;
  ll base = -INF; //ALERT: each custom merge requires different base (+: 0, *: 1, min: INF)
  ll merge(ll a, ll b) {
    return max(a,b);
  }
 
  void dfs(int u, int p = 0) {
    par[u][0] = p;
    for (int i = 1; i < LG; i++) 
      if (par[u][i - 1] != -1) {
        par[u][i] = par[par[u][i - 1]][i - 1];
        val[u][i] = merge(val[u][i - 1], val[par[u][i - 1]][i - 1]);
      }
    for (ii ix : adj[u]) {
      long long v = ix.first, c = ix.second;
      if (v == p) continue;
      dep[v] = dep[u] + 1;
      val[v][0] = c; // ALERT
      dfs(v, u);
    }
  }
 
 
  ii ancestor(int u, int k) {
    ll result = base;
    for (int i = 0; i < LG; i++) 
      if (k & (1 << i)) {
        result = merge(result, val[u][i]);
        u = par[u][i];
      }
    return {u, result};
  }
 
  ii lca(int u, int v) { // {lca, value from path}
    if (dep[u] < dep[v]) swap(u, v);
    ii xx = ancestor(u, dep[u] - dep[v]);
 
    u = xx.first;
    ll result = xx.second;
 
    if (u == v) return xx;
 
    for (int i = LG - 1; i >= 0; i--)
      if (par[u][i] != par[v][i]) {
        result = merge(result, merge(val[u][i], val[v][i]));
        u = par[u][i], v = par[v][i];
      }
    
    int x = par[u][0];
    result = merge(result, val[u][0]);
 
    return {x, result};
  }
 
  LCA (int _n, vector<vector<ii>>& g, int root = 1): adj(g) {
    int n = _n;
    LG = 64 - __builtin_clzll(n);
    par.assign(n + 1, vector<int>(LG, -1));
    val.assign(n + 1, vector<long long>(LG, base));
    dep.assign(n + 1, 0);
    dfs(root);
  }
};