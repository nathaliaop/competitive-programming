int n;
vector<set<int>> adj;
vector<char> ans;
 
vector<bool> removed;
 
vector<int> subtree_size;
 
int dfs(int u, int p = 0) {
	subtree_size[u] = 1;
 
	for(int v : adj[u]) {
		if(v != p && !removed[v]) {
			subtree_size[u] += dfs(v, u);
        }
    }
 
	return subtree_size[u];
}
 
int get_centroid(int u, int sz, int p = 0) {
	for(int v : adj[u]) {
		if(v != p && !removed[v]) {
			if(subtree_size[v]*2 > sz) {
				return get_centroid(v, sz, u);
            }
        }
    }
 
	return u;
}
 
char get_next(char c) {
    if (c != 'Z') return c + 1;
    return '$';
}
 
bool flag = true;
 
void solve(int node, char c) {
	int center = get_centroid(node, dfs(node));
    ans[center] = c;
    removed[center] = true;
 
    for (auto u : adj[center]) {
        if (!removed[u]) {
            char next = get_next(c);
            if (next == '$') {
                flag = false;
                return;
            }
            solve(u, next);
        }
    }
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    adj.resize(n + 1);
    ans.resize(n + 1);
    removed.resize(n + 1);
    subtree_size.resize(n + 1);
 
    for (int i = 1; i <= n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
 
    solve(1, 'A');
 
    if (!flag) cout << "Impossible!\n";
    else {
        for (int i = 1; i <= n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
 
    return 0;
}