/**
 * We will ask you to perfrom some instructions of the following form:
 * 0 i : change the color of the i-th node (from white to black, or from black to white);
 * or
 * 1 v : ask for the id of the first black node on the path from node 1 to node v. if it doesn't exist, you may return -1 as its result.
 * Tested: https://www.spoj.com/problems/QTREE3/en/
*/

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
const int N = 1e6 + 5;

vector<int> adj[N];
int id[N], h[N], head[N], sz[N], pos[N], e[N];
int p[20][N];
int nhanh = 1, cnt;
set<int> s;

void dfs(int u, int par = 1) {
    sz[u] = 1;
    p[0][u] = par;
    for (int i = 1; i < 20; i++)        p[i][u] = p[i - 1][p[i - 1][u]];
    for (int v : adj[u])    if (v != par)   {
        h[v] = h[u] + 1;
        dfs(v,u);
        sz[u] += sz[v];
    }
}

void hld(int u, int par = -1) {
    if (head[nhanh] == 0)       head[nhanh] = u;
    ++cnt;
    e[cnt] = u;
    pos[u] = cnt;
    id[u] = nhanh;
    
    int target = -1;
    for (int v : adj[u])    if (v != par)   {
        if (target == -1 || sz[target] < sz[v])     target = v;
    }
    
    if (target != -1)       hld(target, u);
    
    for (int v : adj[u])    if (v != par)   {
        if (v != target)        {
            ++nhanh;
            hld(v,u);
        }
    }
}

void init() {
    dfs(1);
    hld(1);
}

int query(int l, int r) {
    auto it = s.lower_bound(l);
    if (it == s.end())  return INT_MAX;
    if (*it >= l && *it <= r)       return (*it);
    return INT_MAX;
}

int ans_hld(int u, int v)   {   // u la cha v
    int ans = INT_MAX;
    while (id[u] != id[v]) {
        int v2 = head[id[v]];
        ans = min(ans, query(pos[v2], pos[v]));
        v = p[0][v2];
    }
    ans = min(ans, query(pos[u], pos[v]));
    if (ans == INT_MAX)     return -1;
    return e[ans];
}

void solve() {
    int n,q;    cin >> n >> q;
    for (int i = 1; i < n; i++)     {
        int u,v;    cin >> u >> v;
        adj[u].pb(v);   adj[v].pb(u);
    }
    init();
    while (q--) {
        int typ;    cin >> typ;
        if (typ == 1)   {
            int v;   cin >> v;
            cout << ans_hld(1,v) << '\n';   
        }
        else {
            int v;  cin >> v;
            if (s.find(pos[v]) != s.end())       s.erase(s.find(pos[v]));
            else s.insert(pos[v]);
        }
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(0);  cin.tie(nullptr);   cout.tie(nullptr);
    solve();
    return 0;
}

/*
9 8
1 2
1 3
2 4
2 9
5 9
7 9
8 9
6 8
1 3
0 8
1 6
1 7
0 2
1 9
0 2
1 9 
*/
