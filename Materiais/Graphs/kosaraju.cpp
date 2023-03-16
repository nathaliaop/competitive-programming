// Description:
// Finds all the strongly connected components in a graph
// A strongly connected component is the largest component possible so that
// each node has a path to all of the other nodes

// Problem:
// https://cses.fi/problemset/task/1683/

// Complexity:
// O(V + E) where V is the number of vertices and E is the number of edges

vector<vector<int>> adj, adj_rev;
vector<bool> used;
vector<int> order, component;

void dfs1(int v) {
    used[v] = true;

    for (auto u : adj[v])
        if (!used[u])
            dfs1(u);

    order.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    component.push_back(v);

    for (auto u : adj_rev[v])
        if (!used[u])
            dfs2(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;

    adj.resize(n);
    adj_rev.resize(n);

    while (q--) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    used.assign(n, false);

    for (int i = 0; i < n; i++) {
        if (!used[i]) dfs1(i);
    }

    used.assign(n, false);
    reverse(order.begin(), order.end());

    int curr = 0;
    vector<int> ans(n);

    for (auto v : order) {
        if (!used[v]) {
            dfs2 (v);

            curr++;
            for (auto e : component) {
                ans[e] = curr;
            }

            component.clear();
        }
    }

    cout << curr << '\n';
    for (auto e : ans) {
        cout << e << ' ';
    }
    cout << '\n';

    return 0;
}