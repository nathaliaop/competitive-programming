const int NONE = 0, BLUE = 1, RED = 2;
vector<vector<int>> graph(100005);
vector<bool> visited(100005); 
int color[100005];  

bool bfs(int s = 1){

    queue<int> q;
    q.push(s);
    color[s] = BLUE;
    
    while (not q.empty()){
        auto u = q.front(); q.pop();

        for (auto v : graph[u]){
            if (color[v] == NONE){
                color[v] = 3 - color[u];
                q.push(v);
            } 
            else if (color[v] == color[u]){
                return false;
            }
        }
    }

    return true;
}

bool is_bipartite(int n){

    for (int i = 1; i<=n; i++) 
        if (color[i] == NONE and not bfs(i))
            return false;

    return true;
}