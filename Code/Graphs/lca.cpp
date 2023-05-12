// Description:
// Find the lowest common ancestor between two nodes in a tree

// Problem:
// https://cses.fi/problemset/task/1688/

// Complexity:
// O(log n)

// How to use:
// preprocess(1);
// lca(a, b);

// Notes
// To calculate the distance between two nodes use the following formula
// dist[a] + dist[b] - 2*dist[lca(a, b)]

const int MAX = 2e5+17;

const int BITS = 32;

vector<int> adj[MAX];
// vector<pair<int, int>> adj[MAX];
// int dist[MAX];
 
int timer;
vector<int> tin, tout;
vector<vector<int>> up;
 
void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
 
    for (int i = 1; i <= BITS; ++i) {
        up[v][i] = up[up[v][i-1]][i-1];
    }
   
    for (auto u : adj[v]) {
        if (u != p) {
            dfs(u, v);
        }
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
    for (int i = BITS; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}
 
void preprocess(int root) {
    tin.resize(MAX);
    tout.resize(MAX);
    timer = 0;
    up.assign(MAX, vector<int>(BITS + 1));
    dfs(root, root);
}