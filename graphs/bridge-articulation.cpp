/*
    Usage: Find bridges and articulations
    Tested: https://cses.fi/problemset/task/2076, https://cses.fi/problemset/task/2077
*/

const int N = 1e5 + 5;
int n,m,dfsTime,numBridge;    
vector<int> adj[N];
vector<pair<int,int>> bridges; // All edges that are bridges
int num[N], low[N], tail[N], joint[N];      // joint[i] = 1 <=> i is articulation  

void dfs(int u, int par = -1) {
    int numChild = 0;
    num[u] = low[u] = ++dfsTime;
    for (int v : adj[u]) {
        if (v == par)   continue;
        if (!num[v]) {
            dfs(v,u);
            low[u] = min(low[u], low[v]);
            if (low[v] == num[v])   {
                bridges.push_back({u,v});
                numBridge++;
            }
            numChild++;
            if (par == -1 && numChild > 1)     joint[u] = 1;
            if (par != -1 && low[v] >= num[u])  joint[u] = 1;
        }
        else low[u] = min(low[u], num[v]);
    }
    tail[u] = dfsTime;
}
