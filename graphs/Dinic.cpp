// Maximum flow from s to t in a flow network. O(E*V^2)
// Tested: https://oj.vnoi.info/problem/nkflow
// Tested: https://oj.vnoi.info/problem/nknet

#define ll long long
#define sz(x) (int) (x).size()

const int N = 1e3 + 5;
int n,m,s,t;
int c[N][N];

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vector<int> lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		for (int L = 0; L < 31; L++) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vector<int>(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

signed main() {
    cin >> n >> m >> s >> t;
    Dinic dinic(n + 1);
    for (int i = 1; i <= m; i++) {
        int u,v,C;
        cin >> u >> v >> C;
        dinic.addEdge(u,v,C);
        c[u][v] = 1;
    }  
    cout << dinic.calc(s,t) << '\n';
    
    /// Find all edges in min-cut, can be optimized using edges list
    for (int i = 1; i <= n; i++)        for (int j = 1; j <= n; j++)    {
        if (c[i][j] && dinic.leftOfMinCut(i) && !dinic.leftOfMinCut(j))    
            cout << i << " " << j << '\n';
    }
}