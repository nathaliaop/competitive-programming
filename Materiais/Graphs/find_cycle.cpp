bitset<MAX> visited;
vector<int> path;
vector<int> adj[MAX];

bool dfs(int u, int p){
    
    if (visited[u]) return false;

    path.pb(u);
    visited[u] = true;

    for (auto v : adj[u]){
        if (visited[v] and u != v and p != v){
            path.pb(v); return true;
        }

        if (dfs(v, u)) return true;
    }

    path.pop_back();
    return false;
}

bool has_cycle(int N){

    visited.reset();

    for (int u = 1; u <= N; ++u){
        path.clear();
        if (not visited[u] and dfs(u,-1)) 
            return true;
        
    }

    return false;
}