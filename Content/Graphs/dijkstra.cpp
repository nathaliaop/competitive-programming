const int MAX = 2e5+7;
const int INF = 1000000000;
vector<vector<pair<int, int>>> adj(MAX);

void dijkstra(int s, vector<int> & d, vector<int> & p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;
    set<pair<int, int>> q;
    q.insert({0, s});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                q.erase({d[to], to});
                d[to] = d[v] + len;
                p[to] = v;
                q.insert({d[to], to});
            }
        }
    }
}

vector<int> restore_path(int s, int t) {
    vector<int> path;

    for (int v = t; v != s; v = p[v])
        path.push_back(v);
    path.push_back(s);

    reverse(path.begin(), path.end());
    return path;
}

int adj[MAX][MAX];
int dist[MAX];
int minDistance(int dist[], bool sptSet[], int V) {
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

void dijkstra(int src, int V) {
 
    bool sptSet[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
 
        sptSet[u] = true;
 
        
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && adj[u][v]
                && dist[u] != INT_MAX
                && dist[u] + adj[u][v] < dist[v])
                dist[v] = dist[u] + adj[u][v];
    }
}