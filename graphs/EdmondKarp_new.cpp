// Maximum flow from s to t in a flow network. O(E^2*V)
// Tested: https://oj.vnoi.info/problem/nkflow
// Tested: https://oj.vnoi.info/problem/nknet

const int N = 1e3 + 5;
const int INF = numeric_limits<int>::max() / 2;
int c[N][N], par[N], f[N][N], d[N];
int n,m,s,t;

int bfs(int s, int t) {
    queue<int> q;
    fill(par, par + N, -1);
    fill(d, d + N, 0);
    q.push(s);  d[s] = INF;
    while (!q.empty()) {
        int u = q.front();      q.pop();
        for (int i = 1; i <= n; i++) {
            if (c[u][i] - f[u][i] > 0 && par[i] == -1) {
                d[i] = min(d[u], c[u][i] - f[u][i]);
                par[i] = u;     q.push(i);
                if (i == t)     return d[t];
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int cur = 0, ans = 0;
    while ((cur = bfs(s,t)) > 0) {
        ans += cur;
        int v = t;
        while (v != s) {
            f[par[v]][v] += cur;
            f[v][par[v]] -= cur;
            v = par[v];
        }
    }
    return ans;
}

int vis[N];
void dfs_min_cut(int u) {       /// Find all edges in Min-Cut, edges u-v in Min-Cut has vis[u] = 1 and vis[v] = 0
    vis[u] = 1;
    for (int v = 1; v <= n; v++)        {
        if (abs(f[u][v]) < c[u][v] && !vis[v])     dfs_min_cut(v);
    }
}

vector<pair<int, int>> min_cut()  { // Can optimized using edge list
    dfs_min_cut(s);
    vector<pair<int, int>> ans;
    for (int i = 1; i <= n; i++)        
        for (int j = 1; j <= n; j++) 
            if (f[i][j] && vis[i] && !vis[j])       
                ans.push_back({i,j});
    return ans;
}

signed main() {
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++) {
        int u,v,C;
        cin >> u >> v >> C;
        c[u][v] += C;
    }    
    cout << max_flow(s,t) << '\n';
    auto v = min_cut();
    for (auto ii : v)       cout << ii.first << " " << ii.second << '\n';
    return 0;
}