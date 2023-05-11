#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e5+17;

vector<int> adj[MAX];
bool visited[MAX];

int max_depth = 0, max_node = 1;

void dfs (int v, int depth) {
    visited[v] = true;
    
    if (depth > max_depth) {
        max_depth = depth;
        max_node = v;
    }
    
    for (auto u : adj[v]) {
        if (!visited[u]) dfs(u, depth + 1);
    }
}

int tree_diameter() {
    dfs(1, 0);
    max_depth = 0;
    for (int i = 0; i < MAX; i++) visited[i] = false;
    dfs(max_node, 0);
    return max_depth;
}