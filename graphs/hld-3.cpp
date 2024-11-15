/**
 * Given a rooted tree of  nodes, where each node is uniquely numbered in between [1..N]. The node 1 is the root of the tree. Each node has an integer value which is initially 0.
 * You need to perform the following two kinds of queries on the tree:
     * add t value: Add value to all nodes in subtree rooted at t
     * max a b: Report maximum value on the path from a to b
 * Tested: https://vjudge.net/problem/HackerRank-subtrees-and-paths
*/

#include<bits/stdc++.h>

using namespace std;

#define int long long
#define pb push_back

const int INF = 1e9 + 7;
const int N = 2e5 + 5;

vector<int> adj[N];
int id[N], head[N], sz[N], in[N], out[N], h[N], pos[N];
int p[20][N];
int nhanh = 1, cnt;

int seg[4 * N], lazy[4 * N];

void down(int id) {
    int t = lazy[id];
    int lhs = id * 2, rhs = id * 2 + 1;
    seg[lhs] += t;  seg[rhs] += t;
    lazy[lhs] += t;     lazy[rhs] += t;
    lazy[id] = 0;
}

void update(int id, int l, int r, int u, int v, int val) {
    if (l > v || r < u)     return;
    if (l >= u && r <= v) {
        seg[id] += val;
        lazy[id] += val;
        return;
    }
    down(id);
    int mid = (l + r) / 2;
    update(id * 2, l, mid, u, v, val);
    update(id * 2 + 1, mid + 1, r, u, v, val);
    seg[id] = max(seg[id * 2], seg[id * 2 + 1]);
}

int get(int id, int l, int r, int u, int v) {
    if (l > v || r < u)     return -INF;
    if (l >= u && r <= v)   return seg[id];
    down(id);
    int mid = (l + r) / 2;
    return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}

void dfs(int u, int par = 1) {
    sz[u] = 1;
    p[0][u] = par;
    for (int i = 1; i < 20; i++)        p[i][u] = p[i - 1][p[i-1][u]];
    for (int v : adj[u])    if (v != par) {
        h[v] = h[u] + 1;
        dfs(v,u);
        sz[u] += sz[v];
    }
}

void hld(int u, int par = -1) {
    if (head[nhanh] == 0)       {
        head[nhanh] = u;
    }
    ++cnt;
    in[u] = cnt;
    id[u] = nhanh;
    pos[u] = cnt;
    
    int target = -1;
    for (int v : adj[u])    if (v != par) {
        if (target == -1 || sz[target] < sz[v])     
            target = v;
    }
    
    if (target != -1)   hld(target,u);
    
    for (int v : adj[u])    if (v != par) {
        if (v != target) {
            ++nhanh;
            hld(v,u);
        }
    }
    out[u] = cnt;
}

int query(int u, int v) {
    int ans = -INF;
    while (id[u] != id[v]) {
        if (h[head[id[u]]] > h[head[id[v]]])        swap(v,u);
        int v2 = head[id[v]];
        ans = max(ans, get(1,1,cnt,pos[v2], pos[v]));
        v = p[0][v2];
    }
    if (pos[u] > pos[v])        swap(u,v);
    ans = max(ans, get(1,1,cnt,pos[u], pos[v]));
    return ans;
}

void solve() {
    int n;  cin >> n;
    for (int i = 1; i < n; i++)     {
        int u,v;    cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    
    dfs(1);
    hld(1);
    
    int q;  cin >> q;
    while (q--) {
        string typ;     cin >> typ;
        if (typ == "add")   {
            int u,val;      cin >> u >> val;
            update(1,1,cnt,in[u], out[u], val);
        }
        else {
            int u,v;    cin >> u >> v;
            cout << query(u,v) << '\n';
        }
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    solve();
    return 0;
}

/*
5
1 2
2 3
2 4
5 1
6
add 4 30
add 5 20
max 4 5
add 2 -20
max 4 5
max 3 4
*/
