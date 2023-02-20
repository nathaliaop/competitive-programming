const int MAX = 2e5+17;

int n, l;
vector<vector<int>> adj;
// vector<pair<int, int>> adj[MAX];
// int dist[MAX];

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    /*for (auto [u, peso] : adj[v]) {
        if (u != p) {
            dist[u] = dist[v] + peso;
            dfs(u, v);
        }
    }*/

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(MAX);
    tout.resize(MAX);
    timer = 0;
    up.assign(MAX, vector<int>(32));
    dfs(root, root);
}

//distance between a and b
// dist[a] + dist[b] - 2*dist[lca(a, b)]