int n,m;
vector<int> g[N];

bool onStack[N];
stack<int> st;
int tin[N], low[N];
int dfsTime=0;

int SCCCount=0;

void dfs(int u) {
    onStack[u]=true;st.push(u);
    low[u]=tin[u]=++dfsTime;

    for(int v : g[u]){
       // cout<<u<<" -> "<<v<<endl;
        if (!tin[v]) dfs(v);
        if (onStack[v]) low[u]=min(low[u],low[v]); // low[v] not tin[v]
    }

    if (low[u]==tin[u]){ // new SCC found
        while (!st.empty()){
            int a = st.top();
            onStack[a]=false;st.pop();
            printf("%d ",a);
            if (a == u){
                printf("\n");
                break;
            }
        }
        SCCCount++;
    }
}