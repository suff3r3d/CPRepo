/**
 * Description: Fast bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $btoa$ should be a vector full of
 * -1's of the SAME SIZE as the right partition. Returns the size of
 * the matching. btoa[i] will be the match for vertex i on the right side,
 * or -1 if it's not matched.
 * Usage: vector<int> btoa(m, -1); hopcroftKarp(g, btoa);
 * Time: O(sqrt(V)*E)
 * Tested: https://oj.vnoi.info/problem/match1
 * Tested: https://oj.vnoi.info/problem/fmatch
 */

bool dfs(int a, int L, vector<vector<int>>& g, vector<int>& btoa, vector<int>& A, vector<int>& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vector<int>>& g, vector<int>& btoa) {
	int res = 0;
	vector<int> A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(A.begin(), A.end(), 0);
		fill(B.begin(), B.end(), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
		for (int a = 0; a < g.size(); a++) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
        for (int a = 0; a < g.size(); a++)
			res += dfs(a, 0, g, btoa, A, B);
	}
}

signed main() {
    int n,m,p;
    cin >> n >> m >> p;
    vector<vector<int>> g(n + 1,vector<int>());
    while (p--) {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    vector<int> btoa(m + 1, -1); 
    cout << hopcroftKarp(g, btoa) << '\n';
    
    /// Find all matching, btoa[i] is the left side of i(The right side)
    for (int i = 0; i < btoa.size(); i++)  
        if (btoa[i] != -1)    
            cout << btoa[i] << "->" <<  i << "\n";
}