/**
 * You are given a tree 
 * We will ask you to perfrom some instructions of the following form:
 * CHANGE i ti : change the cost of the i-th edge to ti
 * or
 * QUERY a b : ask for the maximum edge cost on the path from node a to node b
 * Status: Tested: https://vjudge.net/problem/SPOJ-QTREE
*/

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
const int N = 1e5 + 5;

int sz[N];
int n, dfsTime;
int nhanh, cnt;
int id[N]; // <=> thu tu cua chain chua dinh i = id[i]
int head[N]; // <=> gia tri dau tien cua chain thu i = head[i]
int pos[N]; // <=> thu tu cua dinh u sau khi duoc trai phang = pos[i]
int in[N], out[N], h[N], a[N], p[N][20];
vector<int> adj[N];

struct seg2D {  // 0-index
    int n;
    vector<int> seg;
    seg2D() = default;
    seg2D(int _n) : seg(2 * _n, INT_MIN), n(_n) {}
    void update(int u, int val) {
        for (seg[u += n] = val; u > 1; u /= 2)    {
            seg[u >> 1] = max(seg[u], seg[u ^ 1]);
        }
    }
    int get(int u, int v) {
        int ans = INT_MIN;
        for (u += n,v += n; u <= v; u/=2, v /= 2) {
            if (u & 1)      ans = max(ans, seg[u++]);
            if (~v & 1)     ans = max(ans, seg[v--]);
        }
        return ans;
    }
}seg;


void reset() {
    nhanh = 1;
    dfsTime = 0;
    cnt = 0;
    for (int i = 1; i <= n; i++){
        adj[i].clear();
        h[i] = 0;
        in[i] = 0;
        out[i] = 0;
        pos[i] = 0;
        head[i] = 0;
        id[i] = 0;
        a[i] = 0;
        sz[i] = 1;
    }  
    memset(p,0,sizeof p);
}


void dfs(int u, int par = -1) {
    p[u][0] = par;
    for (int i = 1; i < 20; i++)        p[u][i] = p[p[u][i-1]][i-1];
    ++dfsTime;
    in[u] = dfsTime;
    sz[u] = 1;
    for (int v : adj[u])   if (v != par) {
        h[v] = h[u] + 1;
        dfs(v,u);
        sz[u]+=sz[v];
    }
    out[u] = dfsTime;
}

bool cha(int u, int v) {
    return (in[u] <= in[v] && out[u] >= out[v]);
}

void build_hld(int u, int par = -1) {
    if (head[nhanh] == 0) {
        head[nhanh] = u;
    }
    ++cnt;
    pos[u] = cnt;
    id[u] = nhanh;
    
    int tmp = -1;
    for (int v : adj[u])        if (v != par) {
        if (tmp == -1 || sz[tmp] < sz[v])       tmp = v;
    } // Tim dinh v co sz lon nhat
    
    // heavy edge
    if (tmp != -1)      build_hld(tmp,u);
    
    for (int v : adj[u])    if (v != par && v != tmp) {
        /// light edge
        nhanh++;
        build_hld(v,u);
    }
}

int ans_hld(int u, int v) {     // the maximum edge cost on the path from node u to node v
    int ans = INT_MIN;
    while (id[u] != id[v]) {
        if (h[head[id[u]]] > h[head[id[v]]])        swap(u,v);
        int v2 = head[id[v]];
        ans = max(ans, seg.get(pos[v2] - 1, pos[v] - 1));
        v = p[v2][0];
    }
    /// id[u] == id[v]
    if (pos[u] > pos[v])    swap(u,v);
    ans = max(ans, seg.get(pos[u], pos[v] - 1)); /// Khi u va v o cung nhanh, ta chi nhay tu v len dinh gan u nhat vi u o day la lca (ta phai bo a[lca] di do qua trinh chuyen duong di)
    return ans;
}

int lca(int u, int v) { // Bin lift
    if (h[u] < h[v])        swap(u,v);
    int k = h[u] - h[v];
    for (int j = 0; j < 20; j++)    if (k >> j & 1)     u = p[u][j];
    if (u == v)     return u;
    for (int i = 19; i >= 0; i--)   {
        if (p[u][i] != p[v][i])     u = p[u][i], v = p[v][i];
    }
    return p[u][0];
}

void precalc() {
    dfs(1,1);
    build_hld(1);
}

void solve() {
    cin >> n;
    reset();
    vector<array<int,3>> ed(n + 1);
    for (int i = 1; i < n; i++)     {
        int u,v,w;  cin >> u >> v >> w;
        ed[i] = {u,v,w};
        adj[u].pb(v);
        adj[v].pb(u);
    }
    precalc();
    seg = seg2D(cnt);
    for (int i = 1; i < n; i++) {
        int u = ed[i][0], v = ed[i][1], w = ed[i][2];
        if (!cha(u,v))      swap(u,v);
        a[v] = w;
        seg.update(pos[v] - 1, w);
    }
    while (1) {
        string typ;
        cin >> typ;
        if (typ == "DONE")      return;
        if (typ == "QUERY")   {
            int u,v;    cin >> u >> v;
            int LCA = lca(u,v);
            cout << max(ans_hld(u,LCA), ans_hld(v,LCA)) << '\n';
        }
        else {
            int id;     cin >> id;
            int nval;   cin >> nval;
            int u = ed[id][0], v = ed[id][1], w = ed[id][2];
            if (!cha(u,v))      swap(u,v);      // v la con u
            a[v] = nval;
            ed[id][2] = nval;
            seg.update(pos[v] - 1, nval);
        }
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    int test;   cin >> test;
    while (test--) {
        solve();
        cout << '\n';
    }
    return 0;
}

/*
1
3
1 2 1
2 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE
*/